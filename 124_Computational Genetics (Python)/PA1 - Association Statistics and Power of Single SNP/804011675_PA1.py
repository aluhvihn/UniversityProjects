from scipy.stats import norm
import math
import os
import pandas as pd
import numpy as np

file = '\\SNP_Status\\SNP_status.txt'
df = pd.read_csv(os.getcwd()+file, sep=' ', index_col=0)
col = df.columns

SNP_stat = {}

print 'UID:804011675'
print 'email:aluhvihn@ucla.edu'
print 'Undergrad or Grad:Undergrad'

#Iterate through each SNP
for SNP in col:
	#Status column isn't SNP
	if SNP == 'Status':
		break
	
	#Create stats for SNP
	SNP_stat[SNP] = {'case':0.0, 'ctrl':0.0, 'p_case':0.0, 'p_ctrl':0.0, 'p_obvs':0.0, 'S_A':0.0, 'p_value':0.0}
	
	#Go through each individual for SNP to determine case, control counts
	indiv = zip(df[SNP],df['Status'])
	for value, stat in indiv:
		if stat == 'Case':
			SNP_stat[SNP]['case'] += value
		else:
			SNP_stat[SNP]['ctrl'] += value
	
	#Compute probability of case, control, observed for SNP
	SNP_stat[SNP]['p_case'] = SNP_stat[SNP]['case']/2000.0
	SNP_stat[SNP]['p_ctrl'] = SNP_stat[SNP]['ctrl']/2000.0
	SNP_stat[SNP]['p_obvs'] = (SNP_stat[SNP]['p_case'] + SNP_stat[SNP]['p_ctrl']) / 2.0

	#Compute S_A and p values
	if (SNP_stat[SNP]['p_case']-SNP_stat[SNP]['p_ctrl']!=0) and (SNP_stat[SNP]['p_obvs']*(1.0-SNP_stat[SNP]['p_obvs'])>0):
		SNP_stat[SNP]['S_A'] = (SNP_stat[SNP]['p_case']-SNP_stat[SNP]['p_ctrl']) / (math.sqrt(2.0/2000.0) * math.sqrt(SNP_stat[SNP]['p_obvs']*(1.0-SNP_stat[SNP]['p_obvs'])))
	SNP_stat[SNP]['p_value'] = 2*norm.cdf( -abs(SNP_stat[SNP]['S_A']))

print '<A>'
for SNP in col:
	if SNP == 'Status':
		break
	print SNP + ':' + str(SNP_stat[SNP]['p_value'])
print '</A>'

bonferroni = 0.05 / 100000.0
print '<B>'
for SNP in col:
	if SNP == 'Status':
		break
	if SNP_stat[SNP]['p_value'] < bonferroni:
		print SNP
print '</B>'