Sub Main


'Declares SurferApp as an object

 Dim SurferApp As Object



'Creates an instance of the Surfer Application object and assigns it to

'the variable named "SurferApp"

 Set SurferApp = CreateObject("Surfer.Application")



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

 Set MapFrame = Shapes.AddContourMap(GridFileName:=SurferApp.Path+"\Samples\demogrid.grd")



'Declares ContourMap as an object

 Dim ContourMap As Object



'Assigns the contour map properties to the variable named "ContourMap"

 Set ContourMap = MapFrame.Overlays(1)



'Declares Levels as an object

 Dim Levels As Object



'Assigns the Levels collection to the variable named "Levels"

 Set Levels = ContourMap.Levels

 Levels.LoadFile(FileName:=SurferApp.Path+"\Samples\Personal.lvl")





End Sub
