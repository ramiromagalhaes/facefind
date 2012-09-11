#include "SearchOutputWriter.h"

SearchOutputWriter::SearchOutputWriter() {}

void SearchOutputWriter::writeOutput(list<FaceData> &files) {
	cout << "<html><head><title>Output</title><style>.imgbox { margin-bottom: 1em; } .imgbox img { display: block; } .imgbox span {font-size: small; display: block;}</style></head><body>" << endl;

    if ( files.empty() ) {
        cout << "<p>Nenhuma imagem encontrada.</p>" << endl;
    } else {
        for (list<FaceData>::iterator it = files.begin(); it != files.end(); it++) {
            cout << "<div class=\"imgbox\"><img src=" << it->path << " alt=" << it->path << " title=" << it->path << " /><span>Hue rating: " << it->hueRating
            		<< "</span><span>Saturation rating: " << it->saturationRating << "</span>" << "</span><span>Value rating: " << it->valueRating << "</span></div>" << endl;
        }
    }

    cout << "</body></html>" << endl;
}
