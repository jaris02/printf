int _printf(const char *format, ...)
{
	va_list list;
	int printed_chars = 0, printed = 0;
	int flags, width, precision, size, buff_ind = 0;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	char *format_ptr = (char *) format;

	while (*format_ptr != '\0')
	{
		if (*format_ptr != '%')
		{
			buffer[buff_ind++] = *format_ptr;
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			printed_chars++;
			format_ptr++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &format_ptr);
			width = get_width(format, &format_ptr, list);
			precision = get_precision(format, &format_ptr, list);
			size = get_size(format, &format_ptr);
			format_ptr++;
			printed = handle_print(format, &format_ptr, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}
