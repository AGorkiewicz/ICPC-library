CXXFLAGS = -std=c++14 -O2 -Wall -Wextra -Wshadow

pdf: library.tex
	pdflatex -shell-escape library.tex
	pdflatex -shell-escape library.tex

pdf_full: full_library.tex
	pdflatex -shell-escape full_library.tex
	pdflatex -shell-escape full_library.tex

library.tex: scripts/generate_tex list
	scripts/generate_tex list library.tex

full_library.tex: scripts/generate_tex full_list
	scripts/generate_full_tex full_list full_library.tex

clean:
	rm -r *.log *.aux *.toc *.tex _minted-library _minted-full_library
