bool Tree::Has(const std::vector<std::string>& node) const {
    Node const* now = &root;
    for (const auto& name : node) {
        auto it = now->children.find(name);
        if (it == now->children.end()) {
            return false;
        }
        now = &it->second;
    }
    return true;
}

void Tree::Insert(const std::vector<std::string>& node) {
    Node* now = &root;
    for (const auto& name : node) {
        auto it = now->children.find(name);
        if (it == now->children.end()) {
            it = now->children.insert(std::make_pair(name, Node())).first;
        }
        now = &it->second;
    }
}

void Tree::Delete(const std::vector<std::string>& node) {
    if (!Tree::Has(node)) {
        return;
    }
    if (node.empty()) {
        return;
    }
    Node* now = &root;
    for (size_t i = 0; i + 1 < node.size(); ++i) {
        auto it = now->children.find(node[i]);
        now = &it->second;
    }
    now->children.erase(now->children.find(node.back()));
}