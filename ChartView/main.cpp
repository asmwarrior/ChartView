#include <wx/app.h>
#include <wx/event.h>
#include "ChartView.h"
#include "ElementPlotData.h"
#include <wx/image.h>

// Define the MainApp
class MainApp : public wxApp
{
public:
    MainApp() {}
    virtual ~MainApp() {}

    virtual bool OnInit() {
        // Add the common image handlers
        wxImage::AddHandler( new wxPNGHandler );
        wxImage::AddHandler( new wxJPEGHandler );
        
        wxLocale* locale = new wxLocale();
        locale->Init(locale->GetSystemLanguage(), wxLOCALE_LOAD_DEFAULT);
        
        // Exemplo
        std::vector<double> tempo;
        std::vector<double> curvaX;
        std::vector<double> curvaY;
        double sTempo = 0;
        for(int i = 0; i < 1000; ++i) {
            tempo.emplace_back(sTempo);
            curvaX.emplace_back(std::sin(sTempo));
            curvaY.emplace_back(std::cos(sTempo));
            sTempo += 0.01;
        }
        
        std::vector<ElementPlotData> plotDataList;
        
        ElementPlotData plotData;
        plotData.SetName(wxT("Test"));
        plotData.SetCurveType(ElementPlotData::CurveType::CT_TEST);
        plotData.AddData(curvaX, wxT("Curve X"));
        plotData.AddData(curvaY, wxT("Curve Y"));
        plotDataList.push_back(plotData);

        // To add new curve types:
        // In the "ElementPlotData.h" file, add a new flag in the CurveType enum. MUST BE BEFORE THE "NUM_ELEMENTS" FLAG. Example CT_TESTE
        // Add the new curve type in the "ChartView.cpp" file, near line 108. Example:
        // rootElementName[static_cast<unsigned int>(ElementPlotData::CurveType::CT_TEST)] = wxT("Test");

        ChartView* cView = new ChartView(nullptr, plotDataList, tempo);
        SetTopWindow(cView);
        cView->SetIcon(wxICON(aaaa));
        return GetTopWindow()->Show();
    }
};

DECLARE_APP(MainApp)
IMPLEMENT_APP(MainApp)
