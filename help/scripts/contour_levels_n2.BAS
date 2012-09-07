Sub DoProfile1( filename_lvl As String )',  filenames_grd() As String)

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
		ContourMap.LabelFont.Face = "Times New Roman"
		ContourMap.LabelFont.Italic = True
		ContourMap.LabelFont.Size = 6
		MapFrame.Selected = True
		filename_grd0$ = GetFilePath(,"GRD")
	Wend
	' Overlay the selected maps
	Dim MapFrame2 As Object
	Set MapFrame2 = Plot.Selection.OverlayMaps


	MapFrame2.xMapPerPU = 20
	MapFrame2.yMapPerPU = 20

	'MapFrame2.SetLimits

	'Debug.Print filename_lvl$
	'Debug.Print "MapFrame2.Axes.Count"
	'Debug.Print MapFrame2.Axes.Count

	For I = 1 To MapFrame2.Axes.Count
	'	Debug.Print I
	'	Debug.Print MapFrame2.Axes(I).Visible
		MapFrame2.Axes(I).Visible = False
	Next I

	' Save the active document using its current name

	'If Not SurferApp.ActiveDocument.Saved Then
	If Not Plot.Saved Then

		'SurferApp.ActiveDocument.SaveAs


		Dim Path$
		Dim lent, n0, nn As Integer

		'filename$ = GetFilePath("","SRF",CurDir(), "Select data file", 1)
		filename$ = GetFilePath("", "SRF", Path$, "Save result Surfer Document", 1)


		If filename$ <> "" Then
			' Save the document whose window caption is "Plot1"
			'SurferApp.ActiveDocument.SaveAs filename$
			Plot.SaveAs filename$

		        'lent=Len(filename$)
	 	       	'n0=InStrRev(filename$,"\")
		        'nn=lent-n0
 		       	'Fname$=Mid$(filename$,n0+1,nn)
	        	'PathIn$=Mid$(filename$,1,n0-1)

		End If 
	End If 
	'Export into DXF
	'Option 				Action 						Default
 
	'Defaults=1   			Set all options to their default values 			No
	'ForgetOptions=1  		Don't remember options for later use 				No
	'FileCompatibility=14	DXF file compatible with ACAD R14 (or later)
	'FileCompatibility=13	DXF file compatible with ACAD R13 (or earlier)  	14
	'FormatASCII=1			DXF file will be written in ASCII format        	Yes
	'FormatASCII=0			DXF file will be written in Binary format			No
	'ScalingSourceApp=1		Use application-supplied scaling parameters     	Yes
	'ScalingSourceApp=0		Use saved scaling parameters						No
	'SaveScalingInfo=1		Save scaling parameters for later use				No
	'AllColorsSame=1		All colors converted to default color				No
	'AllStylesSame=1		All line styles converted to default line style 	Yes
	'AllWidthsSame=1		All line widths converted to default line width 	No
	'AllTextToAreas=1		All text converted to solid areas					Yes
	'FillSolidAreas=1		Solid area interiors are filled						Yes
	'UseSpatialInfo=1		Use only spatial information						No
	'APPLowerLeftX=N.N		Set application page rectangle lower left X value	N/A
	'APPLowerLeftY=N.N		Set application page rectangle lower left Y value	N/A
	'APPUpperRightX=N.N		Set application page rectangle upper right X value	N/A
	'APPUpperRightY=N.N		Set application page rectangle upper right Y value	N/A
	'DXFLowerLeftX=N.N		Set DXF scaling rectangle lower left X value		N/A
	'DXFLowerLeftY=N.N		Set DXF scaling rectangle lower left Y value		N/A
	'DXFUpperRightX=N.N		Set DXF scaling rectangle upper right X value		N/A
	'DXFUpperRightY=N.N		Set DXF scaling rectangle upper right Y value		N/A

	filename_dxf$ = GetFilePath("", "DXF", Path$, "Save result Surfer Document", 1)
	If filename_dxf$ <> "" Then
		Plot.Export(FileName:=filename_dxf$, _
		Options:= "FormatASCII=0, AllColorsSame=1, AllStylesSame=1, AllWidthsSame=1, AllTextToAreas=1, FillSolidAreas=1")
	End If
End Sub


Sub DoProfile( directory As String, profilename As String, filename_lvl As String,  filenames_grd() As String)

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

	Plot.Selection.DeselectAll

	For J = LBound(filenames_grd) To UBound(filenames_grd)
		filename_grd0$  = filenames_grd(J)

		Debug.Print filename_grd0$

		Set MapFrame = Shapes.AddContourMap(filename_grd0$)
		'Declares ContourMap as an object
		Dim ContourMap As Object
		'Assigns the contour map properties to the variable named "ContourMap"
		Set ContourMap = MapFrame.Overlays(1)
		ContourMap.Levels.LoadFile(filename_lvl)
		ContourMap.FillContours = True
		ContourMap.SmoothContours = srfConSmoothMed
		ContourMap.LabelFont.Face = "Times New Roman"
		ContourMap.LabelFont.Italic = True
		ContourMap.LabelFont.Size = 6
		MapFrame.Selected = True
	Next J
	' Overlay the selected maps
	Dim MapFrame2 As Object
	Set MapFrame2 = Plot.Selection.OverlayMaps


	MapFrame2.xMapPerPU = 20
	MapFrame2.yMapPerPU = 20

	'MapFrame2.SetLimits

	'Debug.Print filename_lvl$
	'Debug.Print "MapFrame2.Axes.Count"
	'Debug.Print MapFrame2.Axes.Count

	For I = 1 To MapFrame2.Axes.Count
	'	Debug.Print I
	'	Debug.Print MapFrame2.Axes(I).Visible
		MapFrame2.Axes(I).Visible = False
	Next I

	' Save the active document using its current name

	'If Not SurferApp.ActiveDocument.Saved Then
	If Not Plot.Saved Then

		'SurferApp.ActiveDocument.SaveAs




		filename_srf$ = directory + "\" + profilename + ".srf"


		If filename_srf$ <> "" Then
			' Save the document whose window caption is "Plot1"
			'SurferApp.ActiveDocument.SaveAs filename$
			Plot.SaveAs filename_srf$
		End If
	End If
	'Export into DXF
	'Option 				Action 						Default

	'Defaults=1   			Set all options to their default values 			No
	'ForgetOptions=1  		Don't remember options for later use 				No
	'FileCompatibility=14	DXF file compatible with ACAD R14 (or later)
	'FileCompatibility=13	DXF file compatible with ACAD R13 (or earlier)  	14
	'FormatASCII=1			DXF file will be written in ASCII format        	Yes
	'FormatASCII=0			DXF file will be written in Binary format			No
	'ScalingSourceApp=1		Use application-supplied scaling parameters     	Yes
	'ScalingSourceApp=0		Use saved scaling parameters						No
	'SaveScalingInfo=1		Save scaling parameters for later use				No
	'AllColorsSame=1		All colors converted to default color				No
	'AllStylesSame=1		All line styles converted to default line style 	Yes
	'AllWidthsSame=1		All line widths converted to default line width 	No
	'AllTextToAreas=1		All text converted to solid areas					Yes
	'FillSolidAreas=1		Solid area interiors are filled						Yes
	'UseSpatialInfo=1		Use only spatial information						No
	'APPLowerLeftX=N.N		Set application page rectangle lower left X value	N/A
	'APPLowerLeftY=N.N		Set application page rectangle lower left Y value	N/A
	'APPUpperRightX=N.N		Set application page rectangle upper right X value	N/A
	'APPUpperRightY=N.N		Set application page rectangle upper right Y value	N/A
	'DXFLowerLeftX=N.N		Set DXF scaling rectangle lower left X value		N/A
	'DXFLowerLeftY=N.N		Set DXF scaling rectangle lower left Y value		N/A
	'DXFUpperRightX=N.N		Set DXF scaling rectangle upper right X value		N/A
	'DXFUpperRightY=N.N		Set DXF scaling rectangle upper right Y value		N/A


	filename_dxf$ = directory + "\" + profilename + ".dxf"
	If filename_dxf$ <> "" Then
		Plot.Export(FileName:=filename_dxf$, _
		Options:= "FormatASCII=0, AllColorsSame=1, AllStylesSame=1, AllWidthsSame=1, AllTextToAreas=1, FillSolidAreas=1")
	End If
End Sub
Sub Main

	Dim directory As String
	Dim profilename As String
	Dim filenames_grd () As String
	Dim J As Integer

	J = 0

	filename_lvl$ = GetFilePath(,"LVL")

	filename_grd0$ = GetFilePath(,"GRD")

	Dim Path$
	Dim lent, n0, nn As Integer

	lent=Len(filename_grd0$)
	n0=InStrRev(filename_grd0$,"\")
	nn=lent-n0
 	Fname$=Mid$(filename_grd0$,n0+1,nn)
	directory=Mid$(filename_grd0$,1,n0-1)

	lent=Len(directory)
	n0=InStrRev(directory,"\")
	nn=lent-n0
 	profilename=Mid$(directory,n0+1,nn)

	Debug.Print directory
	Debug.Print Fname$
	Debug.Print profilename

	While filename_grd0$ <> ""
		ReDim Preserve filenames_grd (J)
		filenames_grd (J) = filename_grd0$
		'Debug.Print filenames_grd$(J)
		filename_grd0$ = GetFilePath(,"GRD")
		J = J + 1
	Wend

	For J = LBound(filenames_grd) To UBound(filenames_grd)
		filename_grd0$  = filenames_grd(J)
		Debug.Print filename_grd0$
	Next J

	DoProfile directory, profilename, filename_lvl, filenames_grd

End Sub
