#pragma once

#include "TextPlacement.h"

#include "../interpreter/IPDFRecursiveInterpreterHandler.h"

#include "TPCollectionState.h"

class TextPlacementsCollector: public IPDFRecursiveInterpreterHandler {
public:
    TextPlacementsCollector();
    virtual ~TextPlacementsCollector();

    // IPDFRecursiveInterpreterHandler implementation
    virtual bool onOperation(const std::string& inOperation,  const PDFObjectVector& inOperands);

private:
    TPCollectionState state;


    void Tc(double inCharSpace);
    void Tw(double inWordSpace);
    void TL(double inLeading);
    void Td(double inX, double inY);
    void setTm(const double (&matrix)[6]);
    void TStar();
    ByteList ToBytesList(PDFObject* inObject);
    void Quote(PDFObject* inObject);

    void textPlacement(const PlacedTextOperation& inTextPlacementOperation);
    void textPlacement(const PlacedTextOperationList& inTextPlacementOperations);


};
