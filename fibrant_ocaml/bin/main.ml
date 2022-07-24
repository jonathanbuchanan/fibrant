open Cmdliner

(* Init Command *)
let init_term = Term.(const ())
let init_info = Cmd.info "init"
let init_cmd = Cmd.v init_info init_term

(* Root Command *)
let root_info = Cmd.info "fibrant"
  ~version:"0.0.1"
  ~doc:"A formal system for checking proofs and writing software."
let root_cmd = Cmd.group root_info [
  init_cmd
]

(* Run! *)
let () = exit (Cmd.eval root_cmd)
