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
    fprintf(fid, 'Mean: %f\r\n', mean(vnorm));
    fprintf(fid, 'Mode: %f\r\n', mode(vnorm));
    fprintf(fid, 'Median: %f\r\n', median(vnorm));
    fprintf(fid, 'Min: %f\r\n', min(vnorm));
    fprintf(fid, 'Max: %f\r\n', max(vnorm));
    fprintf(fid, 'Std dev: %f\r\n\r\n', std(vnorm));
    fprintf(fid, [filename '_' 'normal' '_' num2str(lines*cols) '.csv\r\n']);
    vlog = logistic_data(:);
    fprintf(fid, 'Mean: %f\r\n', mean(vlog));
    fprintf(fid, 'Mode: %f\r\n', mode(vlog));
    fprintf(fid, 'Median: %f\r\n', median(vlog));
    fprintf(fid, 'Min: %f\r\n', min(vlog));
    fprintf(fid, 'Max: %f\r\n', max(vlog));
    fprintf(fid, 'Std dev: %f\r\n', std(vlog));
end
