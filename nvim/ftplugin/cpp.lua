vim.api.nvim_create_user_command('Include', 
 function(args_table)
   local file = os.getenv("HOME").."/.config/nvim/templates/" .. args_table.args
   local n_lines_before = vim.api.nvim_buf_line_count(0)
   vim.cmd("read ".. file);
   local n_lines = vim.api.nvim_buf_line_count(0) - n_lines_before
   local current_pos = vim.api.nvim_win_get_cursor(0)
   local new_pos = {current_pos[1] + n_lines, current_pos[2]}
   vim.api.nvim_win_set_cursor(0, new_pos)
 end
 , {
   nargs = 1,
   complete = function(leadStr)
     local folder = os.getenv("HOME").."/.config/nvim/templates/" 
     local files = {}
     for f in io.popen("ls "..folder):lines() do
       if f:match(leadStr) then
         table.insert(files, f) 
       end
     end
     return files
   end,
 }
)
 


vim.opt.makeprg = [[g++ -g -DDEBUG -Wall -std=c++20 -fconstexpr-depth=5000000 -fconstexpr-loop-limit=2147483647 -fconstexpr-ops-limit=2147483647 -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-sign-compare -o %:r %]]
vim.api.nvim_set_keymap('n', '<F5>', ':w <bar> make <CR>', {})
vim.api.nvim_set_keymap('n', '<F1>', ':cn<CR>', {})
vim.api.nvim_set_keymap('n', '<F2>', ':cp<CR>', {})
vim.opt.errorformat="%f:%l:%c: %t%*[^:]:%m," --%f:%l: %t%*[^:]:%m," 
