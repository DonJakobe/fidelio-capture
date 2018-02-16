library("igraph")

#adj <- matrix(c(0, 100, 0, 0, 0, 10, 10, 0, 0), nrow=3, byrow=TRUE)
xy <- t(read.table(file = "./planeXY"))
adj <- as.matrix(read.table(file = "./plane"))


xy <- t(read.table(file = "./meteorXY"))
adj <- as.matrix(read.table(file = "./meteor"))

grph <- graph_from_adjacency_matrix(adj, mode = "undirected", weighted = TRUE)


plot.igraph(grph,vertex.label=V(grph)$name,layout=xy, edge.color="black",edge.width=E(grph)$weight/10)
#plot(grph)
