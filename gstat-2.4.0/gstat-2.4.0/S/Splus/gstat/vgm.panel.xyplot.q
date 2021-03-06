"vgm.panel.xyplot" <-
function (x, y, type = "p", pch = plot.symbol$pch, col, 
	col.line = plot.line$col, col.symbol = plot.symbol$col, lty = 
	plot.line$lty, cex = plot.symbol$cex, lwd = plot.line$lwd, 
	model = model, labels, ...) 
{
    x <- as.numeric(x)
    y <- as.numeric(y)
    if (length(x) > 0) {
        if (!missing(col)) {
            if (missing(col.line)) 
                col.line <- col
            if (missing(col.symbol)) 
                col.symbol <- col
        }
        plot.symbol <- trellis.par.get("plot.symbol")
        plot.line <- trellis.par.get("plot.line")
        points(x = x, y = y, cex = cex, col = col.symbol, pch = pch)
        if (!missing(model)) {
            ret <- variogram.line(model, max(x))
            lines(x = ret$dist, y = ret$gamma, lty = lty, col = col.line, 
                lwd = lwd)
        }
		if (!is.null(labels))
			text(x = x + 0.03 * max(x), y = y, labels = labels)
    }
}
