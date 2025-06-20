#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include "commit.h"
#include "blob.h"
#include "branch.h"

class MiniGit {
private:
    std::string repo_path;
    std::string minigit_path;
    std::string objects_path;
    std::string refs_path;
    std::string head_path;
    
    std::map<std::string, std::shared_ptr<Blob>> staging_area;
    std::map<std::string, std::shared_ptr<Branch>> branches;
    std::string current_branch;
    
    bool is_initialized;
    
    // Helper methods
    void create_directory_structure();
    std::string compute_hash(const std::string& content);
    void save_blob(const std::shared_ptr<Blob>& blob);
    std::shared_ptr<Blob> load_blob(const std::string& hash);
    void save_commit(const std::shared_ptr<Commit>& commit);
    std::shared_ptr<Commit> load_commit(const std::string& hash);
    void save_head(const std::string& commit_hash);
    std::string load_head();
    void save_branch(const std::shared_ptr<Branch>& branch);
    std::shared_ptr<Branch> load_branch(const std::string& name);
    std::string find_lowest_common_ancestor(const std::string& commit1_hash, const std::string& commit2_hash);
    std::vector<std::string> get_commit_ancestors(const std::string& commit_hash);
    std::map<std::string, std::string> get_file_changes(const std::string& from_hash, const std::string& to_hash);
    std::string merge_files(const std::string& base_content, const std::string& ours_content, const std::string& theirs_content);

public:
    MiniGit(const std::string& path = ".");
    
    // Core functionality
    bool init();
    bool add(const std::string& filename);
    bool commit(const std::string& message);
    bool log();
    bool branch(const std::string& branch_name);
    bool checkout(const std::string& target);
    bool merge(const std::string& branch_name);
    bool diff(const std::string& commit1, const std::string& commit2);
    
    // Utility methods
    bool is_repo_initialized() const { return is_initialized; }
    std::string get_current_branch() const { return current_branch; }
    std::vector<std::string> get_branches() const;
    std::string get_head_commit() const;
}; 