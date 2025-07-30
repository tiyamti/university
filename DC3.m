clc;
clear;

% --- 1. Original Analog Signal ---
fs = 10000;
t = 0:1/fs:0.05;
f = 100;
analog_signal = sin(2*pi*f*t);

% --- 2. PCM Quantization ---
nBits = 8;  
L = 2^nBits;

x_min = min(analog_signal);
x_max = max(analog_signal);
quant_levels = linspace(x_min, x_max, L);
[~, idx] = min(abs(analog_signal' - quant_levels), [], 2);
quantized_signal = quant_levels(idx)';

bin_stream = de2bi(idx - 1, nBits, 'left-msb')';
bitstream = bin_stream(:)';

% --- 3. PCM Waveform Generation ---
bitrate = fs * nBits;               
bit_duration = 1 / bitrate;
t_pcm = 0:bit_duration:(length(bitstream)-1)*bit_duration;
pcm_wave = 2*bitstream - 1;   

% --- 4. QPSK Modulation ---
if mod(length(bitstream),2) ~= 0
    bitstream(end+1) = 0; 
end
bit_pairs = reshape(bitstream, 2, [])';
mapping = [1+1j, -1+1j, -1-1j, 1-1j]/sqrt(2);

symbols = zeros(1, size(bit_pairs,1));
for i = 1:size(bit_pairs,1)
    b = bit_pairs(i,:);
    idx_sym = bi2de(b, 'left-msb') + 1;
    symbols(i) = mapping(idx_sym);
end

fc = 1e6;
samples_per_symbol = 20;
fs_tx = fc * 10;
Ts = 1/fs_tx;
t_mod = 0:Ts:(length(symbols)*samples_per_symbol - 1)*Ts;

tx_signal = zeros(1, length(t_mod));
for i = 1:length(symbols)
    I = real(symbols(i));
    Q = imag(symbols(i));
    t_idx = (i-1)*samples_per_symbol+1 : i*samples_per_symbol;
    tx_signal(t_idx) = I*cos(2*pi*fc*t_mod(t_idx)) - Q*sin(2*pi*fc*t_mod(t_idx));
end

% --- 5. AWGN Channel ---
SNR = 20;
rx_signal = awgn(tx_signal, SNR, 'measured');

% --- 6. QPSK Demodulation ---
rx_symbols = zeros(1, length(symbols));
for i = 1:length(symbols)
    t_idx = (i-1)*samples_per_symbol+1 : i*samples_per_symbol;
    r = rx_signal(t_idx);
    I = 2 * mean(r .* cos(2*pi*fc*t_mod(t_idx)));
    Q = -2 * mean(r .* sin(2*pi*fc*t_mod(t_idx)));
    dists = abs(mapping - (I + 1j*Q));
    [~, idx_min] = min(dists);
    rx_symbols(i) = idx_min - 1;
end

rx_bits = de2bi(rx_symbols, 2, 'left-msb')';
rx_bitstream = rx_bits(:)';

% --- 7. Reconstruct from Received PCM ---
rx_samples_bin = reshape(rx_bitstream, nBits, [])';
rx_indices = bi2de(rx_samples_bin, 'left-msb') + 1;
rx_quantized_signal = quant_levels(rx_indices)';
t_recon = t(1:length(rx_quantized_signal));

% --- 8. Add Natural Noise and Interpolate for Realistic Reconstruction ---
rx_quantized_signal_noisy = rx_quantized_signal + 0.01 * randn(size(rx_quantized_signal));  % simulate ADC/DAC/channel noise
reconstructed = interp1(t_recon, rx_quantized_signal_noisy, t, 'spline');                   % smooth interpolation

% --- 9. Plotting ---
figure('Position', [100, 100, 1200, 750]);

subplot(3,2,1);
plot(t, analog_signal);
title('1. Original Analog Signal');
xlabel('Time'); ylabel('Amplitude');

subplot(3,2,2);
stem(t_pcm(1:100), bitstream(1:100), 'filled');
title('2. PCM Bitstream (Digital Signal)');
xlabel('Time'); ylabel('Bit Value');
ylim([-0.2 1.2]);

subplot(3,2,3);
plot(t_mod(1:1000), tx_signal(1:1000));
title('3. QPSK Modulated Signal');
xlabel('Time'); ylabel('Amplitude');

subplot(3,2,4);
plot(t_mod(1:1000), rx_signal(1:1000));
title('4. Signal After AWGN Channel');
xlabel('Time'); ylabel('Amplitude');

subplot(3,2,5);
plot(t, reconstructed, 'r');
title('5. Reconstructed Signal (with natural noise)');
xlabel('Time'); ylabel('Amplitude');

subplot(3,2,6);
plot(t, analog_signal, 'b', t, reconstructed, 'r--');
legend('Original', 'Reconstructed');
title('6. Comparison');
xlabel('Time'); ylabel('Amplitude');
