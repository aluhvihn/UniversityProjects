#include "BTreeNode.h"
#include <string.h>
#include <stdlib.h>

using namespace std;

/* Leaf node constructor */
BTLeafNode::BTLeafNode()
{
	//set buffer (1024 byte array) initially to 0
	memset(buffer,-1,PageFile::PAGE_SIZE);
	keyCount = 0;
}

/*
 * Read the content of the node from the page pid in the PageFile pf.
 * @param pid[IN] the PageId to read
 * @param pf[IN] PageFile to read from
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTLeafNode::read(PageId pid, const PageFile& pf)
{
	return pf.read(pid, buffer);
}
    
/*
 * Write the content of the node to the page pid in the PageFile pf.
 * @param pid[IN] the PageId to write to
 * @param pf[IN] PageFile to write to
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTLeafNode::write(PageId pid, PageFile& pf)
{ 
	return pf.write(pid, buffer);
}

/*
 * Return the number of keys stored in the node.
 * @return the number of keys in the node
 */
int BTLeafNode::getKeyCount()
{
	int pairSize = sizeof(int) + sizeof(RecordId);
	int maxIndex = PageFile::PAGE_SIZE - sizeof(PageId);	//last 4 bytes = PageId to next leaf node
	int count = 0;
	int i, curKey;
	int* temp = (int *) buffer;

	for(i = 0; i < maxIndex/pairSize * (pairSize/sizeof(int)); i += (pairSize/sizeof(int)))
	{
		memcpy(&curKey, temp, sizeof(int)); 
		if(curKey == -1)
			break;
		count++;

		temp += (pairSize/sizeof(int));
	}
	return count;
}

/*
 * Insert a (key, rid) pair to the node.
 * @param key[IN] the key to insert
 * @param rid[IN] the RecordId to insert
 * @return 0 if successful. Return an error code if the node is full.
 */
RC BTLeafNode::insert(int key, const RecordId& rid)
{
	PageId nextNodePtr = getNextNodePtr();	//last 4 bytes for inserted leaf reconstruction
	int pairSize = sizeof(int) + sizeof(RecordId);
	int maxEntry = (PageFile::PAGE_SIZE - sizeof(PageId))/pairSize;
	int maxIndex = PageFile::PAGE_SIZE - sizeof(PageId);
	int i, curKey;
	int* temp = (int *) buffer;
 
	if (getKeyCount() >= maxEntry)
	{
		return RC_NODE_FULL;
	}

	int pid = rid.pid, sid = rid.sid, pid2 = -1, sid2 = -1, key2 = 0;
	for(i = 0; i < (PageFile::PAGE_SIZE/sizeof(int))-1; i+=3){
		if(temp[i] == -1){
			temp[i] = rid.pid;
			temp[i+1] = rid.sid;
			temp[i+2] = key;
			break;
		}
		else if(temp[i+2] > key){
			pid2 = temp[i];
			sid2 = temp[i+1]; 
			key2 = temp[i + 2];
			temp[i] = pid;
			temp[i+1] = sid;
			temp[i+2] = key;
			key = key2;
			pid = pid2;
			sid = sid2;
		}
	}


	if((pid2 | sid2) == -1) return 0;
	temp[i] = pid2;
	temp[i+1] = sid2;
	temp[i+2] = key2;
	return 0;
}

/*
 * Insert the (key, rid) pair to the node
 * and split the node half and half with sibling.
 * The first key of the sibling node is returned in siblingKey.
 * @param key[IN] the key to insert.
 * @param rid[IN] the RecordId to insert.
 * @param sibling[IN] the sibling node to split with. This node MUST be EMPTY when this function is called.
 * @param siblingKey[OUT] the first key in the sibling node after split.
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTLeafNode::insertAndSplit(int key, const RecordId& rid, 
                              BTLeafNode& sibling, int& siblingKey)
{
	PageId nextNodePtr = getNextNodePtr();	//last 4 bytes for inserted leaf reconstruction
	int pairSize = sizeof(int) + sizeof(RecordId);
	int maxEntry = (PageFile::PAGE_SIZE - sizeof(PageId))/pairSize;
	int maxIndex = PageFile::PAGE_SIZE - sizeof(PageId);

	if(sibling.getKeyCount() != 0) return RC_NODE_FULL;
	int position1, split;

	locate(key, position1);
	position1/=12;
	split = 43;
	if (position1 < split) split--;
	int* temp = (int *) buffer;
	int position2 = split*pairSize;
	int remaining = maxIndex - position2;
	memmove(sibling.buffer, buffer+position2, remaining);
	memmove(sibling.buffer+maxIndex, buffer+maxIndex, sizeof(PageId));
	memset(buffer+position2, -1, remaining);
	if (position1 < split) insert(key, rid);
	else sibling.insert(key,rid);
	int* siblingKey_ptr = (int *) sibling.buffer;
	siblingKey = siblingKey_ptr[2];

	return 0;
}

/**
 * If searchKey exists in the node, set eid to the index entry
 * with searchKey and return 0. If not, set eid to the index entry
 * immediately after the largest index key that is smaller than searchKey,
 * and return the error code RC_NO_SUCH_RECORD.
 * Remember that keys inside a B+tree node are always kept sorted.
 * @param searchKey[IN] the key to search for.
 * @param eid[OUT] the index entry number with searchKey or immediately
                   behind the largest key smaller than searchKey.
 * @return 0 if searchKey is found. Otherwise return an error code.
 */
RC BTLeafNode::locate(int searchKey, int& eid)
{
	int pairSize = sizeof(int) + sizeof(RecordId);
	int i, curKey;
	int* temp = (int *) buffer;

	for(i = 0; i < 255; i+=3)
	{
		if (temp[i] == -1 || temp[i+2] > searchKey) break;
		if (temp[i+2] == searchKey) {
			eid = i*4;
			return 0;
		}
	}

	eid = i*4;
	return RC_NO_SUCH_RECORD;
}

/*
 * Read the (key, rid) pair from the eid entry.
 * @param eid[IN] the entry number to read the (key, rid) pair from
 * @param key[OUT] the key from the entry
 * @param rid[OUT] the RecordId from the entry
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTLeafNode::readEntry(int eid, int& key, RecordId& rid)
{
	int pairSize = sizeof(int) + sizeof(RecordId);
	int entryPos = eid * pairSize;
	int* temp = (int *) buffer;

	if(eid < 0 || eid >= 1016)
	{
		return RC_INVALID_CURSOR;
	}

	rid.pid = temp[eid/4]; 
	rid.sid = temp[(eid/4)+1];
	key = temp[(eid/4)+2];
	
	return 0;
}

/*
 * Return the pid of the next sibling node.
 * @return the PageId of the next sibling node 
 */
PageId BTLeafNode::getNextNodePtr()
{
	PageId pid = 0;	//assume no next node
	int maxIndex = PageFile::PAGE_SIZE - sizeof(PageId);
	int* temp = (int *) buffer;

	pid = temp[255];  //last PageID of buffer
	
	return pid;
}

/*
 * Set the pid of the next slibling node.
 * @param pid[IN] the PageId of the next sibling node 
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTLeafNode::setNextNodePtr(PageId pid)
{
	int maxIndex = PageFile::PAGE_SIZE - sizeof(PageId);
	int* temp = (int *) buffer;
	temp[255] = pid;
	return 0;
}

/* ===================== NON LEAF ===================== */

/* Nonleaf node constructor */
BTNonLeafNode::BTNonLeafNode()
{
	//set buffer (1024 byte array) initially to 0
	memset(buffer,-2,PageFile::PAGE_SIZE);
	keyCount = 0;
}

/*
 * Read the content of the node from the page pid in the PageFile pf.
 * @param pid[IN] the PageId to read
 * @param pf[IN] PageFile to read from
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTNonLeafNode::read(PageId pid, const PageFile& pf)
{
	return pf.read(pid, buffer);
}
    
/*
 * Write the content of the node to the page pid in the PageFile pf.
 * @param pid[IN] the PageId to write to
 * @param pf[IN] PageFile to write to
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTNonLeafNode::write(PageId pid, PageFile& pf)
{ 
	return pf.write(pid, buffer);
}

/*
 * Return the number of keys stored in the node.
 * @return the number of keys in the node
 */
int BTNonLeafNode::getKeyCount()
{
	int pairSize = sizeof(int) + sizeof(PageId);
	int maxIndex = PageFile::PAGE_SIZE - sizeof(PageId);	//last 4 bytes = PageId to next leaf node
	int count = 0;
	int i, curKey;
	int* temp = (int *) buffer;

	for (i = 1; i < (maxIndex/pairSize) * (pairSize/sizeof(int)); i += (pairSize/sizeof(int)))
	{
		if(temp[i] == -2)
			break;
		count++;

	}
	return count;
}

/*
 * Insert a (key, pid) pair to the node.
 * @param key[IN] the key to insert
 * @param pid[IN] the PageId to insert
 * @return 0 if successful. Return an error code if the node is full.
 */
RC BTNonLeafNode::insert(int key, PageId pid)
{
	int pairSize = sizeof(int) + sizeof(RecordId);
	int maxEntry = (PageFile::PAGE_SIZE - sizeof(PageId))/pairSize;
	int maxIndex = PageFile::PAGE_SIZE;
	int i, curKey;
	int* temp = (int *) buffer;
	
	if (getKeyCount() >= maxEntry)
	{
		// return RC_NODE_FULL;
	}

	if(temp[((PageFile::PAGE_SIZE - sizeof(PageId))/(sizeof(PageId) + sizeof(int)))*2-1] != -1) return RC_NODE_FULL;

	int pageID = pid, pageID2 = -1, key2;
	for (i = 0; i < (maxIndex/sizeof(int)); i+=2){
		if (temp[i] == -1) {
			temp[i] = pid;
			temp[i+1] = key;
			break;
		}
		if (temp[i+1] > key) {
			pageID2 = temp[i];
			key2 = temp[i + 1];
			temp[i] = pageID;
			temp[i+1] = key;
			key = key2;
			pageID = pageID2;
		}
	}

	if (pageID2 == -1) return 0;
	temp[i] = pageID2;
	temp[i+1] = key2;
	
	keyCount++;	//insert success; increment key count

	return 0;
}

/*
 * Insert the (key, pid) pair to the node
 * and split the node half and half with sibling.
 * The middle key after the split is returned in midKey.
 * @param key[IN] the key to insert
 * @param pid[IN] the PageId to insert
 * @param sibling[IN] the sibling node to split with. This node MUST be empty when this function is called.
 * @param midKey[OUT] the key in the middle after the split. This key should be inserted to the parent node.
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTNonLeafNode::insertAndSplit(int key, PageId pid, BTNonLeafNode& sibling, int& midKey)
{
	int pairSize = sizeof(int) + sizeof(RecordId);
	int maxEntry = (PageFile::PAGE_SIZE - sizeof(PageId))/pairSize;
	int maxIndex = PageFile::PAGE_SIZE - sizeof(PageId);
	int old = 0;
	if(getKeyCount() < maxEntry)
	{
	}	


	if(sibling.getKeyCount() != 0) return RC_NODE_FULL;
	int* temp = (int *) buffer;
	int split, position1;
	split = 64;
	for (position1 = 1; position1 < 2*maxIndex/(sizeof(int) + sizeof(PageId)) - 1; position1+=2) {
		if (temp[position1] >= key) break;
	}
	position1/=2;
	position1++;
	if (position1 < split) {
		split--;
		old = 1;
	}
	position1 = 2*position1 - 1;
	split = 2*split - 1;
	if (old) midKey = temp[split];
	else {
		if (position1 == split)	midKey = key;
		else midKey = temp[split];
	}
	int position2 = split*sizeof(int)+sizeof(int);
	int remaining = maxIndex - position2;
	memmove(sibling.buffer, buffer+position2, remaining);
	for (int i = position2/4-1; i < 256; i++) {
		temp[i] = -2;
	}
	if (old) insert(key, pid);
	else {
		if (midKey != key) sibling.insert(key, pid);
	}
	return 0;
}

/*
 * Given the searchKey, find the child-node pointer to follow and
 * output it in pid.
 * @param searchKey[IN] the searchKey that is being looked up.
 * @param pid[OUT] the pointer to the child node to follow.
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTNonLeafNode::locateChildPtr(int searchKey, PageId& pid)
{
	int pairSize = sizeof(int) + sizeof(RecordId);
	int i, curKey;
	char* temp = buffer;

	memcpy(&pid, temp, sizeof(PageId));
	temp = temp + sizeof(PageId);     
	curKey = 0;
	i = getKeyCount();
	while (i > 0) {
		memcpy(&curKey, temp, sizeof(int));

		if(curKey > searchKey)
			return 0;

		if (curKey == 0)
			return 0;
		temp += sizeof(int);
		memcpy(&pid, temp, sizeof(PageId));
		temp += sizeof(PageId);
		i--;
	}


	return 0;
}

/*
 * Initialize the root node with (pid1, key, pid2).
 * @param pid1[IN] the first PageId to insert
 * @param key[IN] the key that should be inserted between the two PageIds
 * @param pid2[IN] the PageId to insert behind the key
 * @return 0 if successful. Return an error code if there is an error.
 */
RC BTNonLeafNode::initializeRoot(PageId pid1, int key, PageId pid2)
{
	RC check;
	int* temp, *pages;
	temp = pages = (int *) buffer;
  
  for(int i = 0; i < (PageFile::PAGE_SIZE/sizeof(int)); i++){
      temp[i] = -2;
  }
  
  pages[0] = pid1;
  temp[1] = key;
  pages[2] =  pid2;
	return 0;
}
