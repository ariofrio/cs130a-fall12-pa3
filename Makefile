CXXFLAGS=-std=gnu++0x
LDFLAGS=

SRC=\
     main.o \
		 graph.o

.PHONY: all test clean wikipedia

all: hops

hops: $(SRC)
	$(CXX) $(LDFLAGS) $(SRC) -o $@

test: hops
	test/run_all.sh ./hops

clean:
	rm -f *.o
	rm -f hops

test/wikipedia:
	mkdir -p test/wikipedia
	cd test/wikipedia; \
		wget http://downloads.dbpedia.org/3.8/el/labels_en_uris_el.nt.bz2 & \
		wget http://downloads.dbpedia.org/3.8/el/page_links_en_uris_el.nt.bz2; \
		wait

test/wikipedia/labels: test/wikipedia
	bzcat test/wikipedia/labels_en_uris_el.nt.bz2 | \
		grep -oP '(?<=<http://dbpedia.org/resource/)[^>]+' | \
		grep -v '^#' > $@

test/wikipedia/edges: test/wikipedia
	bzcat test/wikipedia/page_links_en_uris_el.nt.bz2 | \
		sed -e 's-<http://dbpedia.org/resource/--g' \
				-e 's-> <http://dbpedia.org/ontology/wikiPageWikiLink> - follows -' \
				-e 's-> .--' | \
		grep -v '^#' | grep -v ' Category:' > $@

test/21-wikipedia.io: test/wikipedia/labels test/wikipedia/edges
	echo "> verbose" > $@
	echo "> `wc -l test/wikipedia/labels | awk '{print $$1}'`" >> $@
	sed 's/^/> /' test/wikipedia/labels >> $@
	echo "> `wc -l test/wikipedia/edges | awk '{print $$1}'`" >> $@
	sed 's/^/> /' test/wikipedia/edges >> $@
	echo '> 0' >> $@
	echo '> Chemistry Greek' >> $@
	echo '< 3' >> $@
	echo '< Greek Greek_alphabet Astronomy Chemistry ' >> $@
	echo '> Computer Wizard' >> $@
	echo '< -1' >> $@
	echo '< ' >> $@
	echo '> Computer Magic' >> $@
	echo '< -1' >> $@
	echo '< ' >> $@
	echo '> Computer Greek' >> $@
	echo '< 4' >> $@
	echo '< Greek Ancient_Greek_philosophy Science Computer_science Computer ' >> $@
	echo '> Computer Pencil' >> $@
	echo '< 3' >> $@
	echo '< Pencil Writing Painting Computer' >> $@

wikipedia: test/21-wikipedia.io
