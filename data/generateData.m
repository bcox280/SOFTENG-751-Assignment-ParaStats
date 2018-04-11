function [] = generateData(filename, cols, lines, mu, sigma)
% Input:
%       cols:  Number of data points per
%       lines: Number of lines of data
% Output:
%       -dist_numdata_time.csv outputted
% Author:
%       Logan Small

% Comment for predictable randomness
rng('default')

% Generate numbers in matrix
norm_data = random('Normal',mu,sigma,[lines,cols]);
logistic_data = random('Logistic',mu,sigma./1.82,[lines,cols]);

% Write data to csv
csvwrite([filename '_' 'normal' '_' num2str(lines*cols) '.csv'], norm_data);
csvwrite([filename '_' 'logistic' '_' num2str(lines*cols) '.csv'], logistic_data);

% Write ground truth to file
fid = fopen([filename '_' 'summary_stats' '.txt'], 'w');
if fid > 0
    fprintf(fid, [filename '_' 'normal' '_' num2str(lines*cols) '.csv\r\n']);
    vnorm = norm_data(:);
    fprintf(fid, 'Mean: %f\n', mean(vnorm));
    fprintf(fid, 'Mode: %f\n', mode(vnorm));
    fprintf(fid, 'Median: %f\n', median(vnorm));
    fprintf(fid, 'Min: %f\n', min(vnorm));
    fprintf(fid, 'Max: %f\n', max(vnorm));
    fprintf(fid, 'Estimated Variance: %f\n', var(vnorm));
    fprintf(fid, 'Estimated Std dev: %f\n', std(vnorm));
    fprintf(fid, 'Skewness: %f\n', skewness(vnorm));
    fprintf(fid, 'Kurtosis: %f\n', kurtosis(vnorm));
    fprintf(fid, 'Sum: %f\n', sum(vnorm));
    fprintf(fid, ['\n' filename '_' 'logistic' '_' num2str(lines*cols) '.csv\n']);
    vlog = logistic_data(:);
    fprintf(fid, 'Mean: %f\n', mean(vlog));
    fprintf(fid, 'Mode: %f\n', mode(vlog));
    fprintf(fid, 'Median: %f\n', median(vlog));
    fprintf(fid, 'Min: %f\n', min(vlog));
    fprintf(fid, 'Max: %f\n', max(vlog));
    fprintf(fid, 'Estimated Variance: %f\n', var(vlog));
    fprintf(fid, 'Estimated Std dev: %f\n', std(vlog));
    fprintf(fid, 'Skewness: %f\n', skewness(vlog));
    fprintf(fid, 'Kurtosis: %f\n', kurtosis(vlog));
    fprintf(fid, 'Sum: %f\n', sum(vlog));
end
