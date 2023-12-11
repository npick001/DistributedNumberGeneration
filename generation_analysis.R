# Load required libraries
library(stats)
library(randtests)

# Blocking Test for Uniformity
blocking_test <- function(numbers, num_blocks) {
  block_size <- length(numbers) / num_blocks
  block_means <- numeric(num_blocks)
  
  for (i in 1:num_blocks) {
    block_start <- ((i - 1) * block_size) + 1
    block_end <- i * block_size
    block_means[i] <- mean(numbers[block_start:block_end])
  }
  
  return(var(block_means))
}

# Define a function to perform the tests on a given file
perform_tests <- function(file_path, filename, num_simulations) {
  numbers <- scan(file_path, what = numeric(), sep = "\n")
  
  N <- length(numbers)
  bins <- hist(numbers, 30, plot = FALSE)
  
  # Adding a small random noise to break ties
  jittered_numbers <- jitter(numbers, amount = 1e-5)
  
  # Frequency Test (Chi-Square Test for Uniformity)
  chi_square_test <- chisq.test(bins$counts)
  
  # Runs Test for Uniformity
  runs_test <- runs.test(jittered_numbers, alternative="two.sided")
  
  num_simulations <- 10  # Adjust the number of simulations as needed
  fft_results <- numeric(num_simulations)
  
  for (sim in 1:num_simulations) {
    # Simulate a random sequence (replace this with your own simulation logic)
    simulated_data <- runif(N)
    
    # Compute the FFT for the real and simulated data
    dft <- abs(fft(numbers))
    simulated_dft <- abs(fft(simulated_data))
    
    # Calculate the discrepancy between the real and simulated DFTs
    fft_discrepancy <- sum(abs(dft - simulated_dft))
    
    fft_results[sim] <- fft_discrepancy
  }
  
  # Calculate the expected discrepancy for the Fourier Transform Test
  expected_discrepancy <- mean(fft_results)
  
  num_blocks <- 10  # Adjust the number of blocks as needed
  blocking_var <- blocking_test(numbers, num_blocks)
  
  cat("Results for file:", file_path, file = filename, append = TRUE)
  cat("\n\nFrequency Test (Chi-Square Test):\n", file = filename, append = TRUE)
  cat(capture.output(chi_square_test), file = filename, append = TRUE)
  cat("\n\nRuns Test for Independence:\n", file = filename, append = TRUE)
  cat(capture.output(runs_test), file = filename, append = TRUE)
  cat("\n\nDiscrete Fourier Transform Test for Uniformity:", file = filename, append = TRUE)
  cat("\nExpected Discrepancy:", expected_discrepancy, file = filename, append = TRUE)
  cat("\n\nBlocking Test for Uniformity:", file = filename, append = TRUE)
  cat("\nBlocking Variance:", blocking_var, file = filename, append = TRUE)
  cat("\n\n--------------------------------------\n", file = filename, append = TRUE)
  
}

# Define paths
relative_path <- "./DistributedNumberGeneration/Output Files/"
output_path <- "./DistributedNumberGeneration/Uniformity Tests/"

file_list <- dir(path = relative_path, pattern = "stream.txt$")
print(file_list)

# Remove existing result files
unlink(paste0(output_path, "LEAP_FROG_results.txt"))
unlink(paste0(output_path, "RANDOM_TREE_results.txt"))

# Number of fft simulations for each file
number_of_simulations <- 10  # Adjust as needed

for (file_name in file_list) {
  file_path <- paste0(relative_path, file_name)
  result_file <- ifelse(grepl("LEAP_FROG", file_name), "LEAP_FROG_results.txt", "RANDOM_TREE_results.txt")
  output_filepath <- paste0(output_path, result_file)
  
  perform_tests(file_path, output_filepath, number_of_simulations)
}
