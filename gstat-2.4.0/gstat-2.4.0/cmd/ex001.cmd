#
# One variable definition:
# to start the variogram modelling user interface.
#
data(zinc): 'zinc.eas', x=1, y=2, v=3;
method: semivariogram;
set fit = 1;
variogram(zinc): 'zinc.est';
