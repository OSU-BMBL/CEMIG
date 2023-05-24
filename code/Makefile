VER=1.0
DIST=cemig$(VER)
PROGS=cemig
SRCS=Struct.cc Global.cc Write_file.cc AcgtExtensions.cc Hamming.cc Parameter.cc Location.cc MathBasis.cc Locations.cc Vertex.cc Node.cc NodeList.cc PoissonEvaluator.cc Sequence.cc SequenceSet.cc Pattern.cc Pwm.cc Motif.cc MarkovModelMatrix.cc AllPossibleKmers.cc SortedKmers.cc HammingDistanceGraph.cc ClusterEvaluator.cc HammingGraphCluster.cc DeBruijnGraph.cc GraphBuilder.cc Graph.cc Digraph.cc PathsOnDBG.cc MotifSet.cc Program.cc
OBJS=$(SRCS:.cpp=.o) 
CC=g++ -g -std=c++11


LDFLAGS= -lm -fopenmp
CPPFLAGS= -std=c++0x -g -fopenmp -Wall -I.  -DVER=$(VER)
OMPFLAGS= -fopenmp

all: $(PROGS)

${PROGS}: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

.o:
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -f *.o

dist:
	$(MAKE) clean
	cd .. && tar czvf $(DIST).tar.gz $(DIST)/
