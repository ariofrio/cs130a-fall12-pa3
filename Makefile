CXXFLAGS=-std=gnu++0x
LDFLAGS=

SRC=\
     main.o \
		 graph.o

.PHONY: all test clean

all: hops

hops: $(SRC)
	$(CXX) $(LDFLAGS) $(SRC) -o $@

test: hops
	test/run_all.sh ./hops

clean:
	rm -f *.o
	rm -f hops
	rm -f test/wikipedia/labels test/wikipedia/edges

test/wikipedia:
	mkdir -p test/wikipedia
	cd test/wikipedia; \
		wget http://downloads.dbpedia.org/3.8/es/labels_en_uris_es.nt.bz2 & \
		wget http://downloads.dbpedia.org/3.8/es/page_links_en_uris_es.nt.bz2; \
		wait

test/wikipedia/labels: test/wikipedia
	bzcat test/wikipedia/labels_en_uris_es.nt.bz2 | \
		grep -oP '(?<=<http://dbpedia.org/resource/)[^>]+' | \
		grep -v '^#' > $@

test/wikipedia/edges: test/wikipedia
	bzcat test/wikipedia/page_links_en_uris_es.nt.bz2 | \
		sed -e 's-<http://dbpedia.org/resource/--g' \
				-e 's-> <http://dbpedia.org/ontology/wikiPageWikiLink> - follows -' \
				-e 's-> .--' | \
		grep -v '^#' > $@

test/21-wikipedia.io: test/wikipedia/labels test/wikipedia/edges
	echo "> `wc -l test/wikipedia/labels | awk '{print $$1}'`" > $@
	sed 's/^/> /' test/wikipedia/labels >> $@
	echo "> `wc -l test/wikipedia/edges | awk '{print $$1}'`" >> $@
	sed 's/^/> /' test/wikipedia/edges >> $@
	echo '> 0' >> $@

