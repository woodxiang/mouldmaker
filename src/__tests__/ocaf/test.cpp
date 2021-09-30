#include <TDocStd_Application.hxx>
#include <TDataStd_Integer.hxx>
#include <BinDrivers.hxx>
#include <iostream>

int main()
{
  Handle(TDocStd_Application) app = new TDocStd_Application();
  BinDrivers::DefineFormat(app);

  Handle(TDocStd_Document) doc;
  app->NewDocument("BinOcaf", doc);
  if (doc.IsNull())
  {
    std::cout << "Bad" << std::endl;
    return 1;
  }

  TDF_Label mainLabel = doc->Main();
  TDataStd_Integer::Set(mainLabel, 199);

  auto status = app->SaveAs(doc, "test.cbf");
  if(status != PCDM_SS_OK)
  {
    app->Close(doc);
    std::cout << "Save failed." << std::endl;
    return 1;
  }

  app->Close(doc);

  return 0;
}