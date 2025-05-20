-- Copy to clipboard
vim.keymap.set({'n','v','x'}, '<leader>y', '"+y', { noremap = true})
vim.keymap.set({'n','v','x'}, '<leader>Y', '"+yg_', { noremap = true})
vim.keymap.set({'n','v','x'}, '<leader>p', '"+p', { noremap = true})
vim.keymap.set({'n','v','x'}, '<leader>P', '"+P', { noremap = true})

vim.api.nvim_set_keymap('i', 'jk', '<ESC>`^', { noremap = true})
vim.api.nvim_set_keymap('x', '<Tab>', '>gv', {noremap = true}) 
vim.api.nvim_set_keymap('x', '<S-Tab>', '<gv', {noremap = true}) 

-- NERDTree
vim.api.nvim_set_keymap('n', '<leader>n', ':NERDTreeToggle<CR>', {noremap = true})
vim.api.nvim_set_keymap('n', '<tab>', 'gt', {noremap = true}) -- tab goes to the next tab
vim.api.nvim_set_keymap('n', '<S-tab>', 'gT', {noremap = true}) -- shift tab goes to the previous tab
vim.api.nvim_set_keymap('n', "'", "`", { noremap = true }) -- make ' set cursor position to a mark

vim.api.nvim_set_keymap('t', '<esc>', [[<c-\><c-n>]], { noremap = false }) -- escape terminal with <esc>
vim.api.nvim_set_keymap('t', '<C-w>', [[<c-\><c-n><C-w>]], {noremap = true, silent = true}) -- Allow <Ctrl+w> in terminal mode

-- Delete Marks
vim.keymap.set('n', 'dM', function() 
  vim.cmd("delmarks!") -- delete lowercase (local) marks 
  vim.cmd("delmarks A-Z") --  delete uppercase (global) marks
  vim.cmd("wshada!") -- write changes to shada file
  end
)
vim.keymap.set("n", "dm", function()
    local char = vim.fn.getcharstr()  -- Get the next character typed
    vim.cmd("delmarks " .. char)      -- Delete the mark corresponding to that key
end, { noremap = true, silent = true })
