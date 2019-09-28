namelist<-array(c("plot_CLS1.txt","plot_CLS2.txt","plot_CLS3.txt","plot_list.txt"),dim=c(1,4))
pdf(sprintf("plots.pdf"))
apply(X=namelist, MARGIN = 2, 
      FUN = function(a){
	data<-read.delim(a, header = TRUE, sep = "\t", dec = ".", col.names = c("X2", "X1", "X0"))
	plot(x=data$X2,y=data$X1, col='red',
	     xlab = 'line number in raw-data file',
	     ylab = 'frequency, errors', ylim=c(0,5),
	     type='o',
	     main = a)
	par(new=TRUE)
	plot(x=data$X2,y=data$X0,
	     xlab = 'line number in raw-data file', col='blue',
	     ylab = 'frequency, errors', ylim=c(0,5),
	     type='o',
	     main = a)
	legend(x="topright", bty ="n", legend=c(sprintf("frequency"),sprintf("errors")), lty=c(1,1,NA), col = c("red","blue",NA))
})
dev.off()
cat("\n")
