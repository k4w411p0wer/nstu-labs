(TeX-add-style-hook
 "main"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("extreport" "a4paper" "14pt" "oneside" "final")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("mdframed" "framemethod=default") ("inputenc" "utf8") ("babel" "russian" "english") ("mathtext" "warn") ("setspace" "nodisplayskipstretch") ("footmisc" "bottom") ("caption" "nooneline") ("listings" "final") ("ulem" "normalem") ("hyperref" "final" "hidelinks") ("natbib" "square" "numbers" "sort&compress") ("geometry" "a4paper" "left=30mm" "right=10mm" "top=20mm" "bottom=20mm" "nohead" "nofoot" "nomarginpar")))
   (add-to-list 'LaTeX-verbatim-environments-local "minted")
   (add-to-list 'LaTeX-verbatim-environments-local "lstlisting")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "href")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "lstinline")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "lstinline")
   (TeX-run-style-hooks
    "latex2e"
    "extreport"
    "extreport10"
    "mdframed"
    "moreverb"
    "lastpage"
    "pscyr"
    "inputenc"
    "babel"
    "polyglossia"
    "fontspec"
    "cmap"
    "mathtext"
    "extsizes"
    "indentfirst"
    "setspace"
    "perpage"
    "footmisc"
    "tocloft"
    "graphicx"
    "caption"
    "subcaption"
    "rotating"
    "calc"
    "tabularx"
    "amsmath"
    "amsfonts"
    "amssymb"
    "amsthm"
    "fp"
    "enumitem"
    "makecell"
    "multirow"
    "array"
    "icomma"
    "sistyle"
    "verbatim"
    "xcolor"
    "listings"
    "ulem"
    "url"
    "hyperref"
    "natbib"
    "totcount"
    "etoolbox"
    "longtable"
    "pdfpages"
    "gensymb"
    "textcase"
    "lmodern"
    "float"
    "geometry"
    "chngcntr"
    "cool"
    "commath"
    "mathtools"
    "physics"
    "tcolorbox"
    "color"
    "minted"
    "tikz"
    "pgfplots"
    "cleveref")
   (TeX-add-symbols
    '("rfrac" 2)
    '("ignore" 2)
    '("Rmnum" 1)
    '("rmnum" 1)
    '("povernut" 1)
    "sectioncentered"
    "No"
    "totfig"
    "tottab"
    "totref"
    "toteq"
    "z"
    "hyph")
   (LaTeX-add-labels
    "fig:lab1-test"
    "lst:main-cpp1"
    "lst:matrix-hpp1"
    "lst:matrix-cpp1"
    "fig:lab2-test"
    "lst:main-cpp2"
    "lst:matrix-hpp2"
    "lst:matrix-cpp2"
    "fig:lab3-test"
    "fig:lab3-files"
    "lst:main-cpp3"
    "lst:matrix-hpp3"
    "lst:matrix-cpp3"
    "lst:file-hpp3"
    "lst:file-cpp3"
    "fig:lab4-test"
    "lst:main-cpp4"
    "lst:matrix-hpp4"
    "lst:matrix-cpp4"
    "lst:file-hpp4"
    "lst:file-cpp4"
    "fig:lab5-diagram"
    "fig:lab5-test"
    "lst:main-cpp5"
    "lst:matrix-hpp5"
    "lst:matrix-cpp5"
    "lst:file-hpp5"
    "lst:file-cpp5"
    "lst:circularqueue-hpp5"
    "lst:circularqueue-cpp5"
    "fig:lab6-test"
    "lst:main-cpp6"
    "lst:matrix-hpp6"
    "lst:matrix-cpp6"
    "lst:file-hpp6"
    "lst:file-cpp6"
    "lst:circularqueue-hpp6"
    "lst:circularqueue-cpp6"
    "sec:end")
   (LaTeX-add-environments
    "longlisting"
    "explanationx"
    "explanation")
   (LaTeX-add-counters
    "totfigures"
    "tottables"
    "totreferences"
    "totequation")
   (LaTeX-add-lengths
    "fivecharsapprox"
    "lengthWordWhere")
   (LaTeX-add-polyglossia-langs
    '("russian" "mainlanguage" "babelshorthands=true")
    '("english" "otherlanguage" ""))
   (LaTeX-add-fontspec-newfontcmds
    "cyrillicfonttt"
    "cyrillicfont"
    "cyrillicfontsf")
   (LaTeX-add-caption-DeclareCaptions
    '("\\DeclareCaptionLabelFormat{stbfigure}" "LabelFormat" "stbfigure")
    '("\\DeclareCaptionLabelFormat{stbtable}" "LabelFormat" "stbtable")
    '("\\DeclareCaptionLabelFormat{stblisting}" "LabelFormat" "stblisting")
    '("\\DeclareCaptionLabelSeparator{stb}" "LabelSeparator" "stb"))
   (LaTeX-add-xcolor-definecolors
    "LightGray")
   (LaTeX-add-mathtools-DeclarePairedDelimiters
    '("ceil" ""))
   (LaTeX-add-color-definecolors
    "dkgreen"
    "gray"
    "mauve"
    "deepblue"
    "deepred"
    "deepgreen"))
 :latex)

