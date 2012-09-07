Sub Main

Set srf = CreateObject("Surfer.Application")

srf.Visible = True



' Create a blank plot

srf.Documents.Add srfDocPlot

' Create a blank worksheet

srf.Documents.Add srfDocWks



' Open an existing plot

filename$ = GetFilePath(,"SRF")

If filename$ <> "" Then

srf.Documents.Open filename$

End If



' Open the sheet named "Sheet1" from an Excel file

filename$ = GetFilePath(,"XLS")

If filename$ <> "" Then

srf.Documents.Open filename$, "Sheet=Sheet1"

End If



' Close the active document

srf.ActiveDocument.Close



' Save the active document using its current name

If Not srf.ActiveDocument.Saved Then

srf.ActiveDocument.Save

End If



' Save the document whose window caption is "Plot1"

srf.Documents("Plot1").SaveAs "MyDocument"



' Close all documents

srf.Documents.CloseAll

End Sub
