Sub OverlayMapsExample(mapframe1 As Object, mapframe2 As Object)

' Retrieve the parent PlotDocument object

Set plot = mapframe1.Parent



' Clear all selections and then select the two MapFrame objects

plot.Selection.DeselectAll

mapframe1.Selected = True

mapframe2.Selected = True



' Overlay the selected maps

plot.Selection.OverlayMaps

End Sub



'The subroutine would be used Like this:



Sub Main

' Start Surfer and create a blank plot document

Set srf = CreateObject("Surfer.Application")

srf.Visible = True

Set plot = srf.Documents.Add(srfDocPlot)



' Create a contour map and a vector map

gridfile$ = srf.Path + "\samples\demogrid.grd"

Set map1 = plot.Shapes.AddContourMap(gridfile$)

Set map2 = Plot.Shapes.AddVectorMap(gridfile$)



' Call the example subroutine to overlay the maps

OverlayMapsExample map1, map2

End Sub
