Sub Main
'Declares SurferApp as an object
 Dim SurferApp As Object
'Creates an instance of the Surfer Application object and assigns it to
'the variable named "SurferApp"
 Set SurferApp = CreateObject("Surfer.Application")
 Set SurferApp = GetObject(,"Surfer.Application")
 If Err.Number<>0 Then
 Set SurferApp = CreateObject("Surfer.Application")
 End If
'Makes Surfer visible
 SurferApp.Visible = True
'Declares Plot as an object
 Dim Plot As Object
'Creates a plot document in Surfer and assigns it to the variable named
'"Plot"
 Set Plot = SurferApp.Documents.Add(srfDocPlot)
'Declares Shapes as an object
 Dim Shapes As Object
'Assigns the Shapes collection to the variable named "Shapes"
 Set Shapes = Plot.Shapes
'Declares MapFrame as an object
 Dim MapFrame As Object
'Creates a contour map and assigns the map coordinate system to the
'variable named "MapFrame"
' Open an existing grid
filename_lvl$ = GetFilePath(,"LVL")

filename_grd0$ = GetFilePath(,"GRD")

Plot.Selection.DeselectAll

While filename_grd0$ <> ""

 Set MapFrame = Shapes.AddContourMap(filename_grd0$)
'Declares ContourMap as an object
 Dim ContourMap As Object
'Assigns the contour map properties to the variable named "ContourMap"
 Set ContourMap = MapFrame.Overlays(1)
 ContourMap.Levels.LoadFile(filename_lvl)
 ContourMap.FillContours = True
 ContourMap.SmoothContours = srfConSmoothMed
 MapFrame.Selected = True

 filename_grd0$ = GetFilePath(,"GRD")

Wend

' Overlay the selected maps
Dim MapFrame2 As Object
Set MapFrame2 = Plot.Selection.OverlayMaps


MapFrame2.xMapPerPU = 20
MapFrame2.yMapPerPU = 20

'MapFrame.SetLimits

'MapFrame.Axes.Show = False

' Save the active document using its current name

If Not SurferApp.ActiveDocument.Saved Then

'SurferApp.ActiveDocument.SaveAs


Dim Path$
Dim lent, n0, nn As Integer

'filename$ = GetFilePath(,"SRF")
'filename$ = GetFilePath("","SRF",CurDir(), "Select data file", 1)
filename$ = GetFilePath("", "SRF", Path$, "Save result Surfer Document", 1)


If filename$ <> "" Then

' Save the document whose window caption is "Plot1"
SurferApp.ActiveDocument.SaveAs filename$

        lent=Len(filename$)
        n0=InStrRev(filename$,"\")
        nn=lent-n0
        Fname$=Mid$(filename$,n0+1,nn)
        PathIn$=Mid$(filename$,1,n0-1)

'        SurferApp.SetPath  = PathIn$


End If

End If



End Sub
