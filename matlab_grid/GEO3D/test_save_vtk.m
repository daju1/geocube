egg

nam=' ud';
pa1='*.vtk';
[FILENAME, PATHNAME] = uiputfile(pa1, ['save variable' nam ' in format: ' pa1]);
cd(PATHNAME);
SaveAsVtk([PATHNAME FILENAME],ud);

nam=' ud';
pa1='*.cub';
[FILENAME, PATHNAME] = uiputfile(pa1, ['save variable' nam ' in format: ' pa1]);
cd(PATHNAME);
SaveAs3DGrid([PATHNAME FILENAME],ud);

nam=' ud';
pa1='*.raw';
[FILENAME, PATHNAME] = uiputfile(pa1, ['save variable' nam ' in format: ' pa1]);
cd(PATHNAME);
SaveAsRaw([PATHNAME FILENAME],ud);

