#include "SearchOutputWriter.h"

SearchOutputWriter::SearchOutputWriter() {}

void SearchOutputWriter::writeOutput(list<FaceData> &files) {
	cout << "<html><head><title>Output</title><style>.imgbox { margin-bottom: 1em; } .imgbox img { display: block; } .imgbox span {font-size: small;}</style></head><body>" << endl;

    if ( files.empty() ) {
        cout << "<p>Nenhuma imagem encontrada.</p>" << endl;
    } else {
        for (list<FaceData>::iterator it = files.begin(); it != files.end(); it++) {
            cout << "<div class=\"imgbox\"><img src=" << it->path << " /><span>Rating: " << it->rating << "</span></div>" << endl;
        }
    }

    cout << "</body></html>" << endl;
}
