rm(list = ls())

library(stats)
library(tseries)

perform_tests <- function(file_path, filename) {
  numbers <- scan(file_path, what = numeric(), sep = "\n")
  
  N <- length(numbers)
  bins <- hist(numbers, 64, plot = FALSE)
  
  # Adding a small random noise to break ties
  jittered_numbers <- jitter(numbers, amount = 1e-5)
  
  chi_square_test <- chisq.test(bins$counts)
  ks_test <- ks.test(jittered_numbers, "punif", min=min(jittered_numbers), max=max(jittered_numbers))
  
  cat("Results for file:", file_path, "\n\n", file=filename, append=TRUE)
  cat(capture.output(chi_square_test), file=filename, append=TRUE)
  cat("\n", file=filename, append=TRUE)
  cat(capture.output(ks_test), file=filename, append=TRUE)
  cat("\n--------------------------------------\n\n", file=filename, append=TRUE)
}

relative_path = "./DistributedNumberGeneration/Output Files/"
output_path = "./DistributedNumberGeneration/Uniformity Tests/"

file_list <- dir(path = relative_path, pattern = "stream.txt$")
print(file_list)

unlink(paste0(output_path, "LEAP_FROG_results.txt"))
unlink(paste0(output_path, "RANDOM_TREE_results.txt"))

for (file_name in file_list) {
  file_path <- paste0(relative_path, file_name)
  result_file <- ifelse(grepl("LEAP_FROG", file_name), "LEAP_FROG_results.txt", "RANDOM_TREE_results.txt")
  output_filepath <- paste0(output_path, result_file)
  
  #cat("Processing file:", file_path, "\n")
  perform_tests(file_path, output_filepath)
}
