#include "commits_view_model.hpp"

#include "data_access_factory.hpp"

CommitsViewModelDelegate::~CommitsViewModelDelegate() = default;

CommitsViewModel::CommitsViewModel(
    BranchEntry parent_branch_value,
    CommitsViewModelDelegate* delegate_value
) :
    commit_data_access(DataAccessFactory::create_commit_data_access(parent_branch_value)),
    delegate(delegate_value),
    parent_branch(std::move(parent_branch_value))
{
}

std::vector<CommitItem> CommitsViewModel::get_commits() const
{
    return commit_data_access->get_commits();
}
