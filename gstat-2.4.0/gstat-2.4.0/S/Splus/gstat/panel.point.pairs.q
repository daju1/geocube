"panel.point.pairs" <-
function (x, y, type = "p", pch = plot.symbol$pch, col, col.line = 
	plot.line$col, col.symbol = plot.symbol$col, lty = plot.line$lty, 
	cex = plot.symbol$cex, lwd = plot.line$lwd, pairs = pairs, ...) 
{
    x = as.numeric(x)
    y = as.numeric(y)
    if (length(x) > 0) {
        if (!missing(col)) {
            if (missing(col.line)) 
                col.line = col
            if (missing(col.symbol)) 
                col.symbol = col
        }
        plot.symbol = trellis.par.get("plot.symbol")
        plot.line = trellis.par.get("plot.line")
        lpoints(x = x, y = y, cex = cex, col = col.symbol, pch = pch)
        if (!missing(pairs)) {
			for (i in seq(along = pairs[,1])) {
				xx = c(x[pairs[i,1]], x[pairs[i,2]])
				yy = c(y[pairs[i,1]], y[pairs[i,2]])
            	lines(x = xx, y = yy, lty = lty, col = col.line, lwd = lwd)
			}
        }
    }
}
