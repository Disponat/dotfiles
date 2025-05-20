require('plugins')
require('core')
require('mappings')
require('debugger')
require('ai')


-- I couldn't get this to work from within ftplugin
function cpp_init() 
 local file = assert(io.open(os.getenv("HOME") .. "/.config/nvim/templates/cpp_template.cpp"))
 local file_lines = {}  -- Initialize an empty string to store the file content
 for line in file:lines() do
    table.insert(file_lines, line)
 end
 file:close()
 
 vim.api.nvim_buf_set_lines(0, 0, -1, false, file_lines)
 vim.schedule( function() 
   vim.api.nvim_command("/sol")
   vim.api.nvim_feedkeys("o", "n", false)
 end)
end

-- Use a template for new c++ files. Cannot put this in ftplugin
vim.api.nvim_create_autocmd( {'BufNewFile'}, {pattern = '*.cpp', callback = cpp_init}) 

