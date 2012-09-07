#
# One variable definition:
# to start the variogram modelling user interface.
#
data(zinc): 'zinc.eas', x=1, y=2, v=3, log;
variogram(zinc): 0.0651255 Nug(0) + 0.571106 Sph(911.041);
data(): 'locs.eas', x=1, y=2; # prediction locations
set output = 'zincok.out';    # ascii output file
