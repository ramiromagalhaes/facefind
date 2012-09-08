#include "SearchOutputWriter.h"

SearchOutputWriter::SearchOutputWriter() {}

void SearchOutputWriter::writeOutput(list<FaceData> &files) {
    cout << "<html><head><title>Output</title><style>img { display: block; margin-bottom: 1em; }</style></head><body>" << endl;

    if ( files.empty() ) {
        cout << "<p>Nenhuma imagem encontrada.</p>" << endl;
    } else {
        for (list<FaceData>::iterator it = files.begin(); it != files.end(); it++) {
            cout << "<img src=" << it->path << " />" << endl;
        }
    }

    cout << "</body></html>" << endl;
}
