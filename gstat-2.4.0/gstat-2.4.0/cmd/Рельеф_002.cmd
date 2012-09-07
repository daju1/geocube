#
# One variable definition:
# to start the variogram modelling user interface.
#
data(Πελόετ): 'C:\Laboratory\Temp\Πελόετ.eas', x=1, y=2, v=3;
set fit = 1;
variogram(Πελόετ): 'C:\Laboratory\Temp\Πελόετ.est': 1 Nug() + 1 Sph(1000);
set logfile='C:\Laboratory\Temp\Πελόετ.log';
