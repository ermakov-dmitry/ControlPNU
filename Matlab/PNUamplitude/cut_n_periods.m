function matrix = cut_n_periods(vector, time_vector, f, begin_pos)
    T = 1 / f;
    T_len = length(time_vector(time_vector <= T));
    start_T = begin_pos * T_len + 1;
    data = vector(start_T:end);
    time = time_vector(start_T:end);
    matrix = [data, time];
end