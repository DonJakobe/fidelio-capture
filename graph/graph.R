library("igraph")

#adj <- matrix(c(0, 100, 0, 0, 0, 10, 10, 0, 0), nrow=3, byrow=TRUE)
x <- read.table(file = "./planeX")[1,]
y <- read.table(file = "./planeY")[1,]
adj <- as.matrix(read.table(file = "./plane"))

grph <- graph_from_adjacency_matrix(adj, mode = "undirected", weighted = TRUE)


plot.igraph(grph,vertex.label=V(grph)$name,layout=cbind(x, y), edge.color="black",edge.width=E(grph)$weight/10)
#plot(grph)
