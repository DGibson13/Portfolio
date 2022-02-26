# David Gibson
# CSCI 4905
# HW5

library(ggplot2)
library(scales)

###### Question 1
library(readxl)
Data1 <- read_excel("./HW5_D1.xlsx")

p <- ggplot(Data1, aes(x = Year, y = `Attrition Rate`))

p + geom_point(size = 3) +
  geom_hline(aes(yintercept=Avg),
            color = "#0072B2", 
            linetype = "dotted", 
            size = 1) +
  geom_label(aes(x = 2010, y = Avg, label = "Average 7.5%"),
            nudge_x = 1,
            nudge_y = 0.005,
            color = "white", fill = "#0072B2") +
  scale_x_continuous(breaks = seq(2010, 2020, 1)) +
  scale_y_continuous(breaks = seq(0, 0.16, 0.02),
                     labels = percent) +
  theme(axis.line = element_line(color = "grey",
                                 size = 1,
                                 linetype = "solid"),
        panel.background = element_rect(fill = "white"),
        panel.grid.major = element_line(colour = "grey")) +
  ggtitle("Attrition Rate Over Time")

p + geom_line(size = 1) +
  geom_point(size = 3) +
  geom_hline(aes(yintercept=Avg),
             color = "#0072B2", 
             linetype = "dotted", 
             size = 1) +
  geom_label(aes(x = 2010, y = Avg, label = "Average 7.5%"),
             nudge_x = 1.5,
             nudge_y = 0.005,
             color = "white", fill = "#0072B2") +
  scale_x_continuous(breaks = seq(2010, 2020, 1)) +
  scale_y_continuous(breaks = seq(0, 0.16, 0.02),
                     labels = percent) +
  theme(axis.line = element_line(color = "grey",
                                 size = 1,
                                 linetype = "solid"),
        panel.background = element_rect(fill = "white"),
        panel.grid.major = element_line(colour = "grey")) +
  ggtitle("Attrition Rate Over Time")

p + geom_bar(stat="identity") +
  geom_hline(aes(yintercept=Avg),
             color = "#0072B2", 
             linetype = "dotted", 
             size = 1) +
  geom_label(aes(x = 2010, y = Avg, label = "Average 7.5%"),
             nudge_x = 2,
             nudge_y = 0.005,
             color = "white", fill = "#0072B2") +
  scale_x_continuous(breaks = seq(2010, 2020, 1)) +
  scale_y_continuous(breaks = seq(0, 0.16, 0.02),
                     labels = percent) +
  theme(axis.line = element_line(color = "grey",
                                 size = 1,
                                 linetype = "solid"),
        panel.background = element_rect(fill = "white"),
        panel.grid.major = element_line(colour = "grey")) +
  ggtitle("Attrition Rate Over Time")


###### Question 2
Data2 <- read_excel("./HW5_D2.xlsx")

colors <- c("Industry Average"="#ebbd34", "Financial Savings"="#0072B2")

ggplot(Data2, aes(x = Year)) +
  geom_line(aes(y = `Industry Average`, color = "Industry Average"), 
            size = 2) +
            #color = "#ebbd34") +
  geom_line(aes(y = `Financial Savings`, color = "Financial Savings"),
            size = 2) +
            #color = "#0072B2") +
  scale_x_continuous(breaks = seq(2012, 2019, 1),
                     limits = c(2012, 2019)) +
  scale_y_continuous(breaks = seq(700, 900, 20), 
                     limits = c(700, 900)) +
  theme(axis.line = element_line(color = "grey",
                                 size = 1,
                                 linetype = "solid"),
        panel.background = element_rect(fill = "white"),
        panel.grid.major = element_line(colour = "grey")) +
  labs(y = NULL, 
       title = "Bank Index", 
       subtitle = "Financial savings below industry average for first time in 5 years",
       color = "Legend") +
  scale_color_manual(values = colors)


######################
# Clear environment
rm(list = ls())

# Clear packages
detach("package:datasets", unload = TRUE) # For base

# Clear plots
dev.off() # But only if there IS a plot

# Clear console
cat("\014") # ctrl+L
