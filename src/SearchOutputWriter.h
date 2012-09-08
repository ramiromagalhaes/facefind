#ifndef SEARCHOUTPUTWRITER_H
#define SEARCHOUTPUTWRITER_H

#include <iostream>
#include <list>

#include "FaceClassifier.h"

using namespace std;

/*
Example of output

<html><head><title>Output</title><style>img { display: block; margin-bottom: 1em; }</style></head><body>
<img src="../../Imagens/photo.jpg" />
<img src="../../Imagens/tomato2.jpg" />
<img src="../../Imagens/Tomato.png" />
<img src="../../Imagens/radiccio.jpg" />
</body></html>
*/
class SearchOutputWriter
{
    public:
        SearchOutputWriter();
        void writeOutput(list<FaceData> &files);

};

#endif // SEARCHOUTPUTWRITER_H
