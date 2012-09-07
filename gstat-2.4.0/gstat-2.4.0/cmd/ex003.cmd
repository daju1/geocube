#
# One variable definition:
# to start the variogram modelling user interface.
#
data(zinc): 'zinc.eas', x=1, y=2, v=3, log;
variogram(zinc): 0.0651255 Nug(0) + 0.571106 Sph(911.041);
#mask:                 'mask_map';

predictions(zinc): 'zn_skpr.grd';
#variances(zinc):   'zn_skvr';
#set output = 'zincok.out';    # ascii output file
