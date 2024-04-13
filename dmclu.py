#!/usr/bin/env python
# coding: utf-8

# In[14]:


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import *
from sklearn.decomposition import *
from scipy.cluster.hierarchy import *
from sklearn.metrics import *
from sklearn.neighbors import *
from sklearn.datasets import load_iris
from sklearn.preprocessing import *


# In[6]:


data = load_iris()
X, y = pd.DataFrame(data.data, columns=data.feature_names), data.target
X, y


# In[7]:


def preprocessing(df):
    pdf = df.copy(deep=True)
    return pd.DataFrame(StandardScaler().fit_transform(pdf), index=pdf.index, columns=pdf.columns)


# In[21]:


def calculateSilhouetteScores(X, getLabels, kMax, kMin = 2):
    scores = []
    ks = range(kMin, kMax + 1)
    for k in ks:
        scores.append(silhouette_score(X, getLabels(k, X)))
    return ks, scores


# In[30]:


def getPCAComponents(X, n_components = 2):
    pca = PCA(n_components = n_components)
    return pca.fit_transform(X)


# In[65]:


def WCSSScores(X, getInertia, kMax, kMin = 2):
    scores = []
    ks = range(kMin, kMax + 1)
    for k in ks:
        scores.append(getInertia(k, X))
    return ks, scores


# ## Agglomerative Clustering

# In[8]:


aggX = preprocessing(X)


# In[9]:


aggX


# In[25]:


aggGetLabels = lambda k, X : AgglomerativeClustering(n_clusters = k, distance_threshold = None).fit_predict(X)
ks, scores = calculateSilhouetteScores(aggX, aggGetLabels, 10)
plt.plot(ks, scores)
plt.title("Silhouette Score Plot for Optimal K")
plt.show()


# Optimal number of `n_cluster = 2`, since it has the largest silhouette score

# In[33]:


labels = AgglomerativeClustering(n_clusters = 2, distance_threshold = None).fit_predict(X)
c = getPCAComponents(X)
plt.scatter(c[:, 0], c[:, 1], c=labels)
plt.show()


# In[44]:


dendrogram(linkage(X, "complete"))


# ## BIRCH

# In[34]:


birX = preprocessing(X)


# In[35]:


birX


# In[36]:


birGetLabels = lambda k, X : Birch(n_clusters = k, compute_labels = True).fit_predict(X)
ks, scores = calculateSilhouetteScores(birX, birGetLabels, 10)
plt.plot(ks, scores)
plt.title("Silhouette Score Plot for Optimal K")
plt.show()


# In[42]:


labels = Birch(n_clusters = 2, compute_labels = True).fit_predict(X)
c = getPCAComponents(X)
plt.scatter(c[:, 0], c[:, 1], c=labels)
plt.show()


# ## DB Scan

# In[52]:


dbX = preprocessing(X)


# In[53]:


dbX


# In[54]:


MIN_PTS = 2 * X.shape[1]
neighbors = NearestNeighbors(n_neighbors=MIN_PTS).fit(dbX)
distances, indices = neighbors.kneighbors(dbX)
distances = np.sort(distances[:, MIN_PTS - 1], axis = 0)

plt.plot(distances)
plt.show()


# In[55]:


labels = DBSCAN(min_samples = MIN_PTS, eps = 1.25).fit_predict(X)
c = getPCAComponents(X)
plt.scatter(c[:, 0], c[:, 1], c=labels)
plt.show()


# ## OPTICS

# In[57]:


dbX = preprocessing(X)


# In[58]:


dbX


# In[59]:


MIN_PTS = 2 * X.shape[1]
neighbors = NearestNeighbors(n_neighbors=MIN_PTS).fit(dbX)
distances, indices = neighbors.kneighbors(dbX)
distances = np.sort(distances[:, MIN_PTS - 1], axis = 0)

plt.plot(distances)
plt.show()


# In[61]:


labels = OPTICS(min_samples = MIN_PTS, eps = 1.25, xi = 0.05, min_cluster_size=0.2).fit_predict(X)
c = getPCAComponents(X)
plt.scatter(c[:, 0], c[:, 1], c=labels)
plt.show()


# ## KMeans

# In[62]:


kX = preprocessing(X)


# In[64]:


kX


# In[69]:


aggGetLabels = lambda k, X : KMeans(n_clusters = k, n_init = 'auto').fit(X).inertia_
ks, scores = WCSSScores(aggX, aggGetLabels, 10)
plt.plot(ks, scores)
plt.title("WCSS for Optimal K")
plt.show()


# In[70]:


labels = KMeans(n_clusters = 6, n_init = 'auto').fit_predict(X)
c = getPCAComponents(X)
plt.scatter(c[:, 0], c[:, 1], c=labels)
plt.show()

