local gp_conf = {

  providers = {
    anthropic = {
        endpoint = "https://api.anthropic.com/v1/messages",
        secret = {"cat", vim.g.home .. "/.keys/anthropic.txt"}
    },
  },

  agents = { 
    {
      provider = "anthropic", 
      name = "Claude 3.5 Haiku Speaker", 
      chat = true, 
      command = true, 
      -- string with model name or table with model name and parameters 
      model = { model = "claude-3-5-haiku-20241022", temperature = 0.8, top_p = 1 }, 
      system_prompt = "As an AI programming assistant, you will answer concisely and to the best of your ability.", 
    },
    {
      provider = "anthropic", 
      name = "Claude 3.7 Sonnet Speaker", 
      chat = true, 
      command = true, 
      -- string with model name or table with model name and parameters 
      model = { model = "claude-3-7-sonnet-20250219", temperature = 0.8, top_p = 1 }, 
      system_prompt = "As an AI programming assistant, you will answer concisely and to the best of your ability.", 
    },
    {
      provider = "anthropic", 
      name = "Claude 3.7 Sonnet Writer", 
      chat = true, 
      command = true, 
      -- string with model name or table with model name and parameters 
      model = { model = "claude-3-7-sonnet-20250219", temperature = 0.8, top_p = 1 }, 
      system_prompt = "You are an AI programming assistant. You will be asked to write code snippets. "
      .. "All your responses are exclusively code snippets with no other text. "
      .. "You will provide concise and efficient code with no comments.", 
    },
  },

  default_command_agent = "Claude 3.7 Sonnet Writer", 
  default_chat_agent =  "Claude 3.7 Sonnet Speaker",
  chat_template = require("gp.defaults").short_chat_template,
	template_selection = "I have the following code selection:"
		.. "\n\n```{{filetype}}\n{{selection}}\n```\n\n{{command}}",
}

local gp = require("gp")
gp.setup(gp_conf)

vim.api.nvim_create_user_command("GpExplain", function(params)
  gp.config.template_selection = "I have the following code selection, please explain what it does and how it works: \n\n ```{{filetype}}\n{{selection}}\n\n"
  gp.cmd.ChatNew(params, " ") -- gp.nvim ignores the provided text template and uses gp.config.template_selection only
  vim.defer_fn(function() vim.cmd('startinsert') end, 50) -- I couldn't get it to work without a delay
end, { range = true, nargs=1 }
)

vim.api.nvim_create_user_command('GpTroubleshoot ', function(params)
  gp.config.template_selection = "Why is the following code not working as intended? \n\n ```{{filetype}}\n{{selection}}\n\n"
  gp.cmd.ChatNew(params, " ") -- gp.nvim ignores the provided text template and uses gp.config.template_selection only
  vim.defer_fn(function() vim.cmd('startinsert') end, 50) -- I couldn't get it to work without a delay
end, { range = true, nargs=1 }
)

vim.api.nvim_create_user_command('GpImplement', function(params)
  local agent = gp.get_command_agent("Claude 3.7 Sonnet Writer")
  local bufnr = vim.api.nvim_get_current_buf()
  local all_lines = vim.api.nvim_buf_get_lines(bufnr, 0, -1, false)
  local file_content = table.concat(all_lines, "\n")

  local start_line = tostring(params.line1)
  local end_line = tostring(params.line2)
  local template = "Working with the following codebase:\n"
        .. "```{{filetype}}\n" .. file_content .. "\n```\n\n"
				.. "Please implement the functionality described here:\n"
				.. "```\n{{selection}}\n```\n\n"
        .. "Your response will replace lines " .. start_line .. " to " .. end_line

 gp.Prompt(params, gp.Target.rewrite, agent, template,
   nil, -- command will run directly without any prompting for user input
   nil -- no predefined instructions (e.g. speech-to-text from Whisper)
 )
end, { range = true }
)

--Standard gp.nvim 
vim.keymap.set({"v", "i", "n"}, '<C-g><C-n>', "<cmd>GpChatNew vsplit<cr>", { noremap = true } )
vim.keymap.set({"v", "n"}, '<C-g><C-f>', "<cmd>GpChatFinder<cr>", { noremap = true } )
vim.keymap.set({"i", "n"}, '<C-g><C-t>', "<cmd>GpChatToggle<cr>", { noremap = true } )

-- custom functions
vim.keymap.set("v", "<C-g><C-e>", ":'<,'>GpExplain vsplit<cr>", { noremap = true } )
vim.keymap.set("v", "<C-g><C-g>", ":'<,'>GpTroubleshoot vsplit<cr>", { noremap = true } )
vim.keymap.set("v", "<C-g><C-i>", ":'<.'>GpImplement<cr>", { noremap = true})
