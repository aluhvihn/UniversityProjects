import java.io.*;
import java.security.MessageDigest;

public class ComputeSHA {
	public static String getSHA1(String filename) throws Exception
	{
		File inFile = new File(filename);		// Create file object w/ input file info
		FileInputStream in = new FileInputStream(inFile);		// Create FileInputStream from the file

		byte[] buffer = new byte[(int) inFile.length()];			// Create buffer to hold filelength bytes

		in.read(buffer);		// read in the contents of the file into buffer

		MessageDigest SHA_checksum = MessageDigest.getInstance("SHA-1");
		SHA_checksum.update(buffer);

		byte[] checksum = SHA_checksum.digest();
		StringBuffer checksum_hex = new StringBuffer();
		
		for (int i=0; i < checksum.length; i++) {
			// checksum_hex.append(Integer.toHexString(0xFF & checksum[i]));
			checksum_hex.append(Integer.toString((0xFF&checksum[i])+0x100, 16).substring(1));
		}

		in.close();
		return checksum_hex.toString();
	}

	// Take input file from 'args', compute SHA-1 hash
	public static void main(String[] args) throws IOException
	{
		try {
			System.out.println(getSHA1(args[0]));
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
}