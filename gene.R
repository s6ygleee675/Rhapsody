library(ggplot2)

#frequency, error graph
namelist<-array(c("plot_CLS1.txt","plot_CLS2.txt","plot_CLS3.txt","plot_list.txt"),dim=c(1,4))
pdf(sprintf("plots.pdf"))
apply(X=namelist, MARGIN = 2, 
      FUN = function(a){
	data<-read.delim(a, header = TRUE, sep = "\t", dec = ".", col.names = c("X2", "X1", "X0"))
	par(mar = c(5, 5, 3, 5))
	plot(x=data$X2,y=data$X1, col='red',
	     xlab = 'line number in raw-data file',
	     ylab = 'frequency',
	     type='o',
	     main = a)
	par(new=TRUE)
	plot(x=data$X2,y=data$X0, type = "o", xaxt = "n", yaxt = "n",
	     ylab = "", xlab = "", col='blue',
	     yaxt="n", lty=2, ylim=c(0,10),
	     main = a)
	axis(side = 4)
	mtext("errors", side = 4, line = 3)
	legend(x="topleft", legend=c(sprintf("frequency"),sprintf("errors")), lty=c(1,2), col = c("red","blue"))
	}
	)

#position graph
namelist<-array(c("plot_CLS1_position.txt","plot_CLS2_position.txt","plot_CLS3_position.txt","plot_list_position.txt"),dim=c(1,4))
apply(X=namelist, MARGIN = 2, 
      FUN = function(a){
	data<-read.delim(a, header = TRUE, sep = "\t", dec = ".", col.names = c("X2", "X1", "X0"))
	plot(x=data$X2,y=data$X1,
	     xlab = 'line number in raw-data file',
	     ylab = 'positions (eg. 3123.68 >> 3123th line, 68 position)', 
	     ylim =c(min(data$X1)-1,max(data$X1)+1),
	     main = a)
	arrows(data$X2, data$X1-data$X0, data$X2, data$X1+data$X0, angle=90, code=3)
	}
	)

dev.off()
