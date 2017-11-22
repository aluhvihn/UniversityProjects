from scipy.stats import norm
from sklearn import preprocessing
import math
import os
import pandas as pd
import numpy as np

file = '\\gwas_data.txt'
df = pd.read_csv(os.getcwd()+file, sep=' ', index_col=0)
col = df.columns

SNP_stat = {}

print 'UID:804011675'
print 'email:aluhvihn@ucla.edu'
print 'Undergrad or Grad:Undergrad'

indiv_phenotype = df['Phenotype']
mu = sum(indiv_phenotype) / float(len(indiv_phenotype))

#Iterate through each SNP
for SNP in col:
	#Phenotype isn't SNP
	if SNP == 'Phenotype':
		break

	#Create states for SNP
	SNP_stat[SNP] = {}

	#Normalize genotypes
	SNP_scaled = preprocessing.scale(df[SNP])
	df[SNP] = preprocessing.scale(df[SNP])

	# indiv_genotype = df[SNP]
	# indiv_scaled = preprocessing.scale(indiv_genotype)

	#Compute beta
	SNP_stat[SNP]['beta'] = 0
	for geno, pheno in zip(SNP_scaled, indiv_phenotype):
		SNP_stat[SNP]['beta'] += geno*pheno
	SNP_stat[SNP]['beta'] /= 135.0

	#Compute e and sigma. eTe_factor is e_transpose * e
	eTe_factor = 0
	for geno, pheno in zip(SNP_scaled, indiv_phenotype):
		eTe_factor += (pheno - mu - SNP_stat[SNP]['beta'] * geno)**2
	sigma = math.sqrt(eTe_factor/133.0)

	#Compute S and p values
	SNP_stat[SNP]['S'] = SNP_stat[SNP]['beta']*math.sqrt(135.0)/sigma
	SNP_stat[SNP]['p_value'] = 2*norm.cdf( -abs(SNP_stat[SNP]['S']) )

print '<A>'
for SNP in col:
	if SNP == 'Phenotype':
		break
	print SNP + ':' + str(SNP_stat[SNP]['beta']) + ',' + str(SNP_stat[SNP]['p_value'])
print '</A>'

bonferroni = 0.05 / 9509.0
print '<B>'
for SNP in col:
	if SNP == 'Phenotype':
		break
	if SNP_stat[SNP]['p_value'] < bonferroni:
		print SNP
print '</B>'


IND_stat = {}
row = df.index
del df['Phenotype']

#Set x_i and magnitude for each individual
# for indiv in row:
# 	IND_stat[indiv] = {}
# 	IND_stat[indiv]['xi'] = df.loc[indiv].values
# 	IND_stat[indiv]['xi_mag'] = sum(IND_stat[indiv]['xi']*IND_stat[indiv]['xi'])**0.5

# average_k = 0
# for indiv1 in row:
# 	for indiv2 in row:
# 		average_k += (1/135.0) * sum(IND_stat[indiv1]['xi']*IND_stat[indiv2]['xi']) / (IND_stat[indiv1]['xi_mag'] * IND_stat[indiv2]['xi_mag'])
# average_k /= 135.0

average_k = 0
for indiv1 in row:
	for indiv2 in row:
		average_k += (1.0/135.0) * np.dot(df.loc[indiv1].values, df.loc[indiv2].values) / (np.linalg.norm(df.loc[indiv1].values) * np.linalg.norm(df.loc[indiv2].values))
average_k /= (135.0**2)

print '<C>'
print 'AVG_K:' + str(average_k)
print '</C>'