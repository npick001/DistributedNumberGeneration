rm(list = ls())

# Load required libraries
library(stats)
library(tseries)

# Define a function to perform the tests on a given file
perform_tests <- function(file_path) {
  # Read numbers from the file
  numbers <- scan(file_path, what = numeric(), sep = "\n")
  
  N <- length(numbers)
  print(N)
  
  # Perform chi-square test for uniformity
  chi_square_test <- chisq.test(numbers)
  cat("Chi-Square Test for Uniformity:\n")
  print(chi_square_test)
  
  # Perform Kolmogorov-Smirnov test
  ks_test <- ks.test(numbers, (1:N)/N)
  cat("\nKolmogorov-Smirnov Test:\n")
  print(ks_test)
  
  # Perform runs test
  runs_test <- runs.test(numbers)
  cat("\nRuns Test for Independence:\n")
  print(runs_test)
}

  # file_pattern
  relative_path = "./DistributedNumberGeneration/Output Files/"
  
  # cat("Current working directory:", getwd(), "\n")
  # cat("Files in the directory:", list.files(path = relative_path), "\n")
  # 
  # test_pattern <- "LEAP_FROG_proc"
  # test_files <- list.files(path = relative_path, pattern = test_pattern)
  # print(test_files)
  
  # Find files matching the pattern
  file_list <- list.files(path = relative_path)
  print(file_list)
  
  # Iterate over the files and perform tests
  for (file_name in file_list) {
    file_path <- paste0(relative_path, file_name)
    cat("Processing file:", file_path, "\n")
    perform_tests(file_path)
    cat("\n")
  }

