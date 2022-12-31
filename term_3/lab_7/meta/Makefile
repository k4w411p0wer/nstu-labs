all: build run

build:
	latexmk -xelatex -synctex=1 -shell-escape -jobname=main main.tex

run:
	evince main.pdf &

clean:
	rm -f *.aux \
	*.fdb_latexmk \
	*.fls \
	*.lof \
	*.lot \
	*.log \
	*.out \
	*.synctex.gz \
	*.xdv \
	*.toc
