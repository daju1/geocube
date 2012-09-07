Sub Main

'Declare object and string variables used in the script

Dim SurferApp, Plot, ContourMapFrame, ContourMap As Object

Dim InFile, GridFile, BaseName As String



'Create the Surfer Application object and assign it to the "SurferApp" variable

Set SurferApp = CreateObject("Surfer.Application")

SurferApp.Visible = True 'Make Surfer visible



'Prompt the user for the name of the data file to process.

'InFile = GetFilePath("","DAT;TXT;CSV;XLS",CurDir(), "Select data file", 0)

'If InFile = "" Then End 'Can't continue: no file was selected

' Open an existing plot

filename$ = GetFilePath(,"SRF")

If filename$ <> "" Then

'srf.Documents.Open filename$

End If



'Get file name without the extension (for example, "week5.txt" becomes "week5")

BaseName = InFile

ExtStart = InStrRev(InFile,".")

If ExtStart > 1 Then BaseName = Left(InFile,ExtStart-1)



'Create a grid from the specified data file using the Kriging algorithm

GridFile = BaseName + ".grd"

'SurferApp.GridData DataFile:=InFile, Algorithm:=srfKriging, _

'DupMethod:=srfDupNone, ShowReport:=False, OutGrid:=GridFile



'Create a plot document in Surfer and assign it to the variable named "Plot"

Set Plot = SurferApp.Documents.Add(srfDocPlot)



'Create a contour map. Assign the map frame to the "ContourMapFrame" variable

'Set ContourMapFrame = Plot.Shapes.AddContourMap(GridFile)



'Assign the contour map properties to the variable named "ContourMap"

Set ContourMap = ContourMapFrame.Overlays(1)



ContourMap.FillContours = True 'Fill the contour map levels

Plot.PrintOut 'Print the page on the default printer

Plot.SaveAs(BaseName + ".srf") 'Save the map

End Sub

