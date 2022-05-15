function [amplitude, phase] = calc_amplitude(y, u, u_ampl, u_f, d_time)
    if (size(y) ~= size(u))
        ME = MException('y size not equal u size', str);
        throw(ME)
    end
    a2i = 0;
    b2i = 0;
    n = length(y);
    for i = 1:n
        a2i = a2i + y(i) * sin(2 * pi * u_f * i * d_time) * 2 / n;
        b2i = b2i + y(i) * cos(2 * pi * u_f * i * d_time) * 2 / n;
    end
    amplitude = 20 * log10((a2i^2 + b2i^2) / u_ampl);
    % amplitude = sqrt(a2i^2 + b2i^2);
    phase = atan2(b2i, a2i);
end