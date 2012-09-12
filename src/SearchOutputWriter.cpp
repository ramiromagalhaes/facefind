#include "SearchOutputWriter.h"

SearchOutputWriter::SearchOutputWriter() {}

void SearchOutputWriter::writeOutput(list<FaceData> &faces) {
	cout << "<html><head><title>Output</title><style>.imgbox { margin-bottom: 1em; } .imgbox img { display: block; } .imgbox span {font-size: small; display: block;}</style></head><body>" << endl;

    if ( faces.empty() ) {
        cout << "<p>Nenhuma imagem encontrada.</p>" << endl;
    } else {
    	cout << "<p>" << faces.size() << " imagens encontradas.</p>" << endl;
        for (list<FaceData>::iterator it = faces.begin(); it != faces.end(); it++) {
            cout << "<div class=\"imgbox\"><img src=" << it->path << " alt=" << it->path << " title=" << it->path << " /><span>Hue rating: " << it->hueRating
            		<< "</span><span>Saturation rating: " << it->saturationRating << "</span>" << "</span><span>Value rating: " << it->valueRating << "</span><span>Final rating: " << it->finalRating << "</span></div>" << endl;
        }
    }

    cout << "</body></html>" << endl;
}
