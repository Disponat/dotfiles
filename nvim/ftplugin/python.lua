vim.g.python3_host_prog = vim.g.home .. '/repos/scripts/venv3.12/bin/ipython'

-- iron also has a list of commands, see :h iron-commands for all available commands
vim.api.nvim_set_keymap('n', '<leader>rs', '<cmd>IronRepl<cr>', {noremap = true}) -- Show/hide REPL
vim.api.nvim_set_keymap('n', '<leader>rr', '<cmd>IronRestart<cr>', {noremap = true})

vim.api.nvim_set_keymap('n','<leader>af','<cmd>ALEFix autopep8<cr>', {noremap = true}) -- ALE fix with autopep8

local iron = require('iron')
iron.core.setup {
  config = {
    -- Whether a repl should be discarded or not
    scratch_repl = true,
    repl_definition = {
      python = {
        command = { vim.g.python3_host_prog, '--no-autoindent' }, -- Note: bash aliases won't work here (something to do with non-interactive bash?)
        format = require("iron.fts.common").bracketed_paste_python,
      }
    },
    repl_open_cmd = "horizontal split"
  },
  keymaps = {
     visual_send = "<F9>",
     send_file = "<F9>",
  },
  highlight = {
    italic = true
  },
  ignore_blank_lines = true, -- ignore blank lines when sending visual select lines
}

local SetVenv = function(input) 
    if not input or input == "" then
      print("Empty python path provided.")
      return
    end

    local filepath = vim.fn.expand(input)
    local filename = vim.fn.fnamemodify(filepath, ":t")
    if filename ~= 'ipython' then
      print('\n Must pass ipython executable')
      return 
    end
    vim.g.python3_host_prog = filepath
    iron.config.repl_definition.python.command = {filepath, "--no-autoindent"}
    require("dap-python").setup(vim.g.python3_host_prog)
end

vim.api.nvim_create_user_command("Venv", function()
    vim.ui.input( {prompt = "Enter ipython path: "}, SetVenv )
end, {})

vim.api.nvim_set_keymap('n', '<leader>rv', '<cmd>Venv<cr>', {noremap = true})

-- look for .env file in current folder
local cwd = vim.fn.expand("%:p:h")
local root = vim.fn.finddir(".git", cwd .. ";") -- search upward for .git
if root == ".git" or root == "" then
  root = cwd -- .git is in current folder or just wasn't found
else 
  root = vim.fs.dirname(root)
end

local env_file = root .. '/.env'
if vim.fn.filereadable(env_file) == 1 then
  local python_path = vim.fn.readfile(env_file)[1]
  print("Using venv: " .. python_path)
  SetVenv(python_path)
else
  print("Using default venv: " .. vim.g.python3_host_prog)
end

