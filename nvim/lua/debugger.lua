require("dap-python").setup(vim.g.python3_host_prog)

vim.api.nvim_set_hl(0, 'DapBreakpoint', { ctermbg=0, fg='#993939', bg='#31353f' })
vim.api.nvim_set_hl(0, 'DapStopped', { ctermbg=0, bg='#565e73' })
vim.fn.sign_define('DapBreakpoint', { text='⬤', texthl='DapBreakpoint', linehl='', numhl=''})
vim.fn.sign_define('DapStopped', { text='', texthl='', linehl='DapStopped', numhl= '' })

local dap, dapui = require("dap"), require("dapui")
vim.diagnostic.config({
  float = {
    border = "rounded",  -- optional, for aesthetics
  },
})

dap.adapters.cppdbg = {
  id = 'cppdbg',
  type = 'executable',
  command = "/usr/local/bin/vscode-cpptools/debugAdapters/bin/OpenDebugAD7",
}

dap.configurations.cpp = {
  {
    name = "Launch file",
    type = "cppdbg",
    request = "launch",
    preLaunchTask = function()
      vim.cmd('make');
    end,
    program = function()
      return vim.fn.input('Path to executable: ', vim.fn.getcwd() .. '/', 'file')
    end,
    cwd = '${workspaceFolder}',
    stopAtEntry = true,
    setupCommands = {
      {
        text = "-enable-pretty-printing",
        description = "Enable pretty printing for STL",
        ignoreFailures = false,
      },
    },
  },
}

-- Requires a venv with debugpy to be active
dap.configurations.python = {
   {
   type = 'python',
   request = 'launch',
   name = 'Launch file',
   program = '${file}',  -- Runs the currently open file
   justMyCode = false,   -- Allows stepping into libraries and standard Python code
 }
}

dapui_opts = {
  icons = { expanded = "⮟", collapsed = "➤", current_frame = "" },
  controls = {
    enabled = false
  },
  layouts = {
    {
      elements = {
        { id = "console", size = 0.4 },
        { id = "repl", size = 0.6 },
      },
      size = 10,
      position = "bottom",
    },
    {
      elements = {
        { id = "scopes", size = 0.75 },
        { id = "watches", size = 0.25 },
      },
      size = 0.4,
      position = "left",
    },
  },
}
dapui.setup(dapui_opts)

dap.listeners.before.attach.dapui_config = function() dapui.open() end
dap.listeners.before.launch.dapui_config = function() dapui.open() end
-- dap.listeners.before.event_terminated.dapui_config = function() dapui.close() end
-- dap.listeners.before.event_exited.dapui_config = function() dapui.close() end

vim.keymap.set('n', '<Leader>dc', function() if vim.bo.modified then vim.cmd("w") end; dap.continue() end)
vim.keymap.set('n', '<Leader>do', function() dap.step_over() end)
vim.keymap.set('n', '<Leader>di', function() dap.step_into() end)
vim.keymap.set('n', '<Leader>dO', function() dap.step_out() end)
vim.keymap.set('n', '<Leader>db',  function() dap.toggle_breakpoint() end)
vim.keymap.set('n', '<Leader>b',  function() dap.toggle_breakpoint() end)
vim.keymap.set('n', '<Leader>dq',  function() dap.disconnect({ terminateDebuggee = true }); dapui.close(); end)
vim.keymap.set('n', '<Leader>dr', function() dap.repl.open() end)
vim.keymap.set('n', '<Leader>dl', function() dap.run_last() end)

vim.keymap.set("n", "<Leader>?", function()
  vim.diagnostic.open_float(nil)
end)
vim.api.nvim_set_keymap('t', '<C-w>', [[<c-\><c-n><C-w>]], {noremap = true, silent = true}) -- Allow <Ctrl+w> in terminal mode
