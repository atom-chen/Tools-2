std::list<Vertex*> getShortestPath(unsigned int startId, unsigned int endId);
std::list<Vertex*> buildPath(Vertex *endVert);

void initializeNodes(unsigned int startId, unsigned int endId);
Vertex *m_startVert, *m_endVert;