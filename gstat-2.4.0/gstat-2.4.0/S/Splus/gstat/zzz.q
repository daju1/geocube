".First.lib" <-
function(lib, pkg) {
	setOldClass(c("variogram", "data.frame"))
	setOldClass(c("variogram.cloud", "data.frame"))
	setOldClass(c("variogram.model", "data.frame"))
	setOldClass(c("point.pairs", "data.frame"))
	setOldClass(c("gstat", "list"))
	.Call("gstat_init", as.integer(1))
}
variogram <- function(object, ...) UseMethod("variogram")
