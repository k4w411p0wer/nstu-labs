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
    "pgfplots")
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
    "sec:intro"
    "sec:defrag"
    "fig:menu-main"
    "fig:menu-quit"
    "fig:menu-open"
    "fig:menu-close"
    "fig:menu-save"
    "fig:menu-defrag"
    "fig:menu-show"
    "fig:menu-find"
    "fig:menu-add"
    "fig:menu-remove"
    "fig:menu-help"
    "sec:end"
    "sec:application"
    "sec:application1")
   (LaTeX-add-environments
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

